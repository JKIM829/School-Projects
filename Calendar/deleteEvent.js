function deleteEvent(id){
    var dataString = "id=" + encodeURIComponent(id) +  "&tok=" + encodeURIComponent(tok);
    var xmlHttp = new XMLHttpRequest(); 
	xmlHttp.open("POST", "deleteEvent.php", true); 
	xmlHttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    
	xmlHttp.addEventListener("load", function(event){
		var jsonData = JSON.parse(event.target.responseText); 
		if(jsonData.success){
            console.log("Success ");
            tok = jsonData.tok;
            updateCalendar();
			console.log(jsonData.message);  //you'll want to clear the add event field afterwards, and display the event on the calendar
		}else{
			var err = document.getElementById("err");
			err.innerHTML = jsonData.message;
		}
	}, false); 
	xmlHttp.send(dataString);
}