document.addEventListener("DOMContentLoaded", initialize, false);
var socketio = io();
var username = "";
var currentRoom = 'public chatroom';

function initialize(){
        document.getElementById("send").addEventListener("click", sendMessage, false);
        document.getElementById("login").addEventListener("click", addUser, false);
        document.getElementById("createRoom").addEventListener("click", createRoom, false);
        document.getElementById("sendpm").addEventListener("click", function(){
                var message = document.getElementById('private_message_input').value;
                var user = document.getElementById("sendpm").value;
                socketio.emit('pm', {toUser: user, msg:message});
                $('#private_message_input').val("");
                }, false);
        
        $("#message_input").keyup(function(event){
                if(event.keyCode == 13){
                        $("#send").click();
                }
        });
        $("#username").keyup(function(event){
                if(event.keyCode == 13){
                        $("#login").click();
                }
        });
        $("#private_message_input").keyup(function(event){
                if(event.keyCode == 13 && $("#private_message_input").val()!=="" ){
                        $("#sendpm").click();
                }
        });
        
        $("#logged").children().hide();
        $("#private_sendbox").hide();
        $("#kickUsers").hide();
}

function addUser(){
    var u = document.getElementById("username").value;
    if(u === ""){
        return;
    }
    socketio.emit("log_in", {user: u});
}

socketio.on("connection", function(){
        socketio.join(currentRoom); 
});


function sendMessage(){
        if(username === ""){
                sysMsg("Log in first");
                return;
        }
         var msg = document.getElementById("message_input").value;
         if(msg !==""){
         document.getElementById("message_input").value = "";
         socketio.emit("message_to_server", {message:msg, user: username});
         }
}

function makeSidebar(user, rooms){
         $("#unlogged").children().hide();
         $("#logged").children().show();
         $("#private_sendbox").hide();
         $("#welcome").append(document.createTextNode("Welcome, " + user));
         makeRoomList(rooms);
         
         $( function() {
                  $( "#accordion" ).accordion({
                  collapsible: true,
                  heightStyle: "content"
                  });
         } );

}

socketio.on("user_added", function(data){
         if(!data.message){
                sysMsg("Sorry, that username has already been taken");
                return;
         }
         
         if(data.message){
                  username = data.username;
                  makeSidebar(data.username, data.rooms);
                  socketio.emit('room_details');
         }
         
         });

socketio.on("message_to_client",function(data) {
         addMsg(data.message, data.user);
      });


socketio.on("system_msg", function(data){
        sysMsg(data.message);
});

function sysMsg(msg){
         document.getElementById("chatlog").appendChild(document.createElement("hr"));
         var fullMsg = $("<div> </div>");
         var msgNode = $("<div></div>").attr("class", "sysNode");
         msgNode.append(document.createTextNode(msg));
         fullMsg.append(msgNode);
          $("#chatlog").append(fullMsg);
         $("#chatlog")[0].scrollTop =  $("#chatlog")[0].scrollHeight;
}

function addMsg(msg, user){
       
         document.getElementById("chatlog").appendChild(document.createElement("hr"));
         var fullMsg = $("<div> </div>");
         var msgNode = $("<div></div>").attr("class", "msgNode");
         var u = $("<div>" + user + "</div>").attr("class", "msgNode poster");
         
         if(user == username){
                  u.attr("class", "msgNode poster me");
                  msgNode.attr("class", "msgNode meNode");
                  var $me = $("<p></p>");
                  $me.append(document.createTextNode(msg));
                  msgNode.append($me);
                  fullMsg.append(msgNode);
                  fullMsg.append(u);
                  $("#chatlog").append(fullMsg);
                  $("#chatlog")[0].scrollTop =  $("#chatlog")[0].scrollHeight;
         }
         
         else{
         var $other = $("<p></p>");
         $other.append(document.createTextNode(msg));
         msgNode.append($other);
         fullMsg.append(msgNode);
         fullMsg.append(u);
         $("#chatlog").append(fullMsg);
         $("#chatlog")[0].scrollTop =  $("#chatlog")[0].scrollHeight;
         }
}

function pm(msg, user, recipient){
     document.getElementById("chatlog").appendChild(document.createElement("hr"));
         var fullMsg = $("<div> </div>");
         var msgNode = $("<div></div>").attr("class", "msgNode private");
         var u = $("<div>" + user + "</div>").attr("class", "msgNode poster");
         if(user == username){
                msgNode = $("<div></div>").attr("class", "msgNode meNode private");
                u =  $("<div>" + "PM to " + recipient + "</div>").attr("class", "msgNode poster meNode");
         }
         var $other = $("<p></p>");
         $other.append(document.createTextNode(msg));
         msgNode.append($other);
         fullMsg.append(msgNode);
         fullMsg.append(u);
         $("#chatlog").append(fullMsg);
         $("#chatlog")[0].scrollTop =  $("#chatlog")[0].scrollHeight;
}

function createRoom(){
        var name = $("#roomName").val();
        if(name === ""){
                $("#err").html("Please enter a room name");
                return;
        }
        var pubBool = $("#pubOption").prop('checked');
        $("#private_sendbox").hide();
        socketio.emit('add_room', {room: name, owner:username, pubOp:pubBool});
}