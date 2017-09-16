// Require the functionality we need to use:
var http = require('http'),
	url = require('url'),
	path = require('path'),
	mime = require('mime'),
	path = require('path'),
	socketio = require('socket.io'),
	fs = require('fs');
	
// Make a simple fileserver for all of our static content.
// Everything underneath <STATIC DIRECTORY NAME> will be served.
var app = http.createServer(function(req, resp){
	var filename = path.join(__dirname, "static", url.parse(req.url).pathname);
	(fs.exists || path.exists)(filename, function(exists){
		if (exists) {
			fs.readFile(filename, function(err, data){
				if (err) {
					// File exists but is not readable (permissions issue?)
					resp.writeHead(500, {
						"Content-Type": "text/plain"
					});
					resp.write("Internal server error: could not read file");
					resp.end();
					return;
				}
 
				// File exists and is readable
				var mimetype = mime.lookup(filename);
				resp.writeHead(200, {
					"Content-Type": mimetype
				});
				resp.write(data);
				resp.end();
				return;
			});
		}else{
			// File does not exist
			resp.writeHead(404, {
				"Content-Type": "text/plain"
			});
			resp.write("Requested file not found: "+filename);
			resp.end();
			return;
		}
	});
	
	
});
app.listen(3456);

var io = socketio.listen(app);
var users = [];
var clients = [];
var Rooms = [{room: 'public chatroom', owner: "sys", members: [], activeMembers:[], publicRoom:true}
			 ];
var defaultRoom = [];
defaultRoom.push(Rooms[0].room);

function removeA(val, arr) {
	var index = -1;
	if(typeof arr == 'undefined'){
		return;
	}
	for(var i = 0; i<arr.length; ++i){
		if(arr[i] == val){
			index = i;
			break;
		}
	}
	arr.splice(i,1);
	return arr;
}



io.on("connection", function(socket){
	var room = "";
	var u = "";
	var current_room_index = -1;
	// This callback runs when a new Socket.IO connection is established.
		
	socket.on('disconnect', function () {
		if(current_room_index >-1){
			var temp = Rooms[current_room_index].activeMembers;
			temp = removeA(socket.username, temp);
			Rooms[current_room_index].activeMembers = temp;
			io.sockets.to(socket.current_room).emit("system_msg", {room:socket.current_room, message: socket.username + " has left the room"});
					var owner_of_room = (Rooms[current_room_index].owner == socket.username);
			io.sockets.to(socket.current_room).emit('update_room', {room: socket.current_room, currentUsers: temp, publicRooms: findPublicRooms(), own:owner_of_room});
		}
		}
	);
	
	socket.on('leave', function(){
		console.log('trying to leave ');
	var temp = Rooms[socket.current_room_index].activeMembers;
	temp = removeA(socket.username, temp);
	Rooms[socket.current_room_index].activeMembers = temp;
	socket.leave(socket.current_room);
	var result = findPublicRooms();
	var owner_of_room = (Rooms[current_room_index].owner);
	io.sockets.to(socket.current_room).emit("system_msg", {room:socket.current_room, message: socket.username + " has been kicked from the room"});
	io.sockets.to(socket.current_room).emit("update_room", {room: socket.current_room, currentUsers: Rooms[socket.current_room_index].activeMembers, publicRooms: result, own:owner_of_room});
	joinRoom(Rooms[0].room);
	});
	
	socket.on('message_to_server', function(data){
		io.sockets.to(socket.current_room).emit("message_to_client",{message:data.message, user: data.user});
		console.log(data.user + " : "+data.message + " in ROOM " + socket.current_room); // log it to the Node.JS output
	});

	
	socket.on('server_message', function(data){
		io.sockets.to(socket.current_room).emit("system_msg", {message:data.message});
	});
	
	socket.on('add_room', function(data){
		if(findRoomIndex(data.room)>=0){
			socket.emit("errMsg", {message: "Sorry, that room name has already been taken."});
			return;
		}
		var newRoom = {room: data.room, owner: socket.username, members: [], activeMembers:[], publicRoom:data.pubOp};
		console.log(newRoom.room + " " + newRoom.publicRoom);
		var index = findUserIndex();
		Rooms.push(newRoom);
		var temp = users[index].rooms;
		temp.push(data.room);
		users[index].rooms = temp;
		changeRoom(data.room);
		socket.emit("update_room", {room: socket.current_room, currentUsers: Rooms[current_room_index].activeMembers, publicRooms: findPublicRooms(), own:Rooms[current_room_index].owner});			
	});
	
	socket.on('change_room', function(data){
		var newroom = data.room;
		if(newroom == socket.current_room){
			return;
		}
		else{
			changeRoom(newroom);
			socket.emit("update_room", {room: socket.current_room, currentUsers: Rooms[current_room_index].activeMembers, publicRooms: findPublicRooms(), own:Rooms[current_room_index].owner});			
		}	
		
	});
	
	socket.on('kick_user', function(data){
		var kicked = data.user;
		console.log(kicked);
		clients[getSocketId(kicked)].emit('been_kicked', {message: true});
	});
	
	socket.on('pm', function(data){
		var recipient = data.toUser;
		clients[getSocketId(recipient)].emit('privateM', {message:data.msg, user:socket.username, received:recipient});
		socket.emit('privateM', {message:data.msg, user:socket.username, received:recipient });
	});
	
	socket.on('room_details', function(){
		var pubRooms = findPublicRooms();
		var owner_of_room = (Rooms[current_room_index].owner);
		socket.emit("update_room", {room: socket.current_room, currentUsers: Rooms[current_room_index].activeMembers, publicRooms: pubRooms, own:owner_of_room});
	});
	
	socket.on('log_in', function(data){
		var user = data.user;
		u = user;
		for(var i = 0; i<users.length; ++i){
			if(users[i].u == user || user == "sys"){
				socket.username = "";
				socket.emit("user_added", {message: false});
				return;
			}
		}
		var newUser = {u:user, rooms: defaultRoom, id: socket.id};
		users.push(newUser);
		clients[socket.id] = socket;
		socket.username = user;
		joinRoom('public chatroom');
		socket.emit("user_added", {message: true, username: user, rooms: defaultRoom});
		
		});
	
	
	
function joinRoom(newRoom){
	if(socket.current_room == newRoom){
		socket.emit("system_msg", {message:"You're already in this chatroom..."});
	}
	var i = findRoomIndex(newRoom);
	current_room_index = i;
	if(i < 0){
		socket.emit('system_msg', {message: "Room does not exist"});
		return;
	}
	socket.current_room_index = i;
	var temp = Rooms[i].activeMembers;
	temp.push(socket.username);
	Rooms[i].activeMembers = temp;
	socket.join(newRoom);
	socket.current_room = newRoom;
	io.sockets.to(newRoom).emit("system_msg", {message: socket.username + " has joined this chatroom"});
	var result = findPublicRooms();
	var owner_of_room = (Rooms[current_room_index].owner);
	io.sockets.to(newRoom).emit('update_room', {room: socket.current_room, currentUsers: Rooms[i].activeMembers, publicRooms: result, own: owner_of_room});
}

function changeRoom(newRoom){
	var index = findRoomIndex(newRoom);
		if(Rooms[index].publicRoom || checkMembers(socket.username, index) || Rooms[index].owner == socket.username){
			leaveRoom();
			joinRoom(newRoom);
		}
}

function leaveRoom(){
	var temp = Rooms[socket.current_room_index].activeMembers;
	temp = removeA(socket.username, temp);
	Rooms[socket.current_room_index].activeMembers = temp;
	socket.leave(socket.current_room);
	var result = findPublicRooms();
			var owner_of_room = (Rooms[current_room_index].owner);
	io.sockets.to(socket.current_room).emit("system_msg", {room:socket.current_room, message: socket.username + " has left the room"});
	io.sockets.to(socket.current_room).emit("update_room", {room: socket.current_room, currentUsers: Rooms[socket.current_room_index].activeMembers, publicRooms: result, own:owner_of_room});
	
}

function checkMembers(user, r){
	var arr = Rooms[r].members;
	for(var i = 0; i<arr.length; ++i){
		if(arr[i] == user){
			return true;
		}
	}
	return false;
}

function findRoomIndex(findroom){
	for(var i =0 ;i<Rooms.length; ++i){
		if(Rooms[i].room == findroom){
			return i;
		}
	}
	return -1;
}

function findUserIndex(){
	var index = -1;
	for(var i =0 ;i<users.length; ++i){
			if(users[i].u == socket.username){
				return i;
			}
		}
		return index;
}

function getSocketId(user){
	for(var i =0 ;i<users.length; ++i){
		if(users[i].u == user){
			return users[i].id;
		}
	}
}

function findPublicRooms(){
	var result = [];
	for(var i = 0; i<Rooms.length; ++i){
		if(Rooms[i].publicRoom === true){
			result.push(Rooms[i].room);
		}
	}
	return result;
	
}

	
});


