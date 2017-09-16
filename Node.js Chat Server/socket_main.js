socketio.on('update_room', function(data){
     $("#curr_room").empty();
     $(".pmList").empty();
     $("#pubrooms").empty();
     
     $("#curr_room").collapse("show");
     $("#newRoom").collapse("hide");
    $("#rooms").collapse("hide");
    $("#kick").collapse("hide");
    $("#pubrooms").collapse("hide");
    var name = data.room;
    var currentUsers = data.currentUsers;
    var size = currentUsers.length;
    var pubRooms = data.publicRooms;
    var $name = $("<b>" + name + "</b>");
    var $size = $("<p>Room size: " + size + "</p>");
    var $li = $("<div></div>").attr('class','memberList');
    $("#curr_room").append($name);
    $("#curr_room").append($size);
    
    if(data.own == username){
        $("#kick").empty();
        $("#kickUsers").show();
        for(var k = 0; k < size; ++k){
            var e = $("<button>" + currentUsers[k] + "</button>").attr({class: "kickable", value:currentUsers[k] });
            $("#kick").append(e);
            $("#kick").append($("<br>"));
        }
        
        $(".kickable").each(function(){
        $(this).on("click", function(){
            var val = $(this).val();
            socketio.emit('kick_user',{user:val} );
        });
    });
    }
    
    for(var i = 0; i< size; ++i){
        var Entry =$("<button>" + currentUsers[i] + "</button>");
        Entry.attr({class: 'pmList', value: currentUsers[i]});
        $li.append(Entry);
        $li.append(document.createElement("br"));
    }
    
    $("#curr_room").append($li);
    
    $(".pmList").each(function(){
        $(this).on("click", function(){
            $("#private_message_input").val('');
            var val = $(this).val();
            makePMBox(val);
        });
    });
    
    for(var j = 0; j<pubRooms.length; ++j){
        var r = $("<button>" + pubRooms[j] + "</button>").attr({class: 'pubRoomList', value: pubRooms[j]});
        $("#pubrooms").append(r);
         }
         
    $(".pubRoomList").each(function(){
        $(this).on("click", function(){
            $("#curr_room").empty();
            var val = $(this).val();
            socketio.emit('change_room',{room:val} );
        });
    });
   
   
   
    
});

socketio.on('privateM', function(data){
    pm(data.message, data.user, data.received);
});

socketio.on('been_kicked', function(data){
    if(data.message)
    $("#chatlog").empty();
    sysMsg("You have been kicked from the chat. Now returning to public chatroom");
    socketio.emit('leave', {message:true});
});

socketio.on('errMsg', function(data){
    $("#err").html(data.message);
});

socketio.on('changed_room', function(data){
    $("#chatlog").empty();
    makeRoomList(data.rooms);
});

function log (message) {
    sysMsg(message);
  }
  
function makeRoomList(rooms){
    $("#rooms").empty();
    for(var i = 0; i<rooms.length; ++i){
        var r = $("<button>" + rooms[i] + "</button>").attr({class: 'roomList', value: rooms[i]});
        $("#rooms").append(r);
         }
         
    $(".roomList").each(function(){
        $(this).on("click", function(){
            var val = $(this).val();
            $("#curr_room").empty();
            socketio.emit('change_room',{room:val} );
        });
    });
  
}
function makePMBox(u){
    $("#private_message_input").attr('placeholder', 'Send a private message to ' + u);
    $("#sendpm").attr('value', u);
    $("#private_sendbox").show();
}
