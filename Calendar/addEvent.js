function addEventForm(){
    $('#EventStuff').append(document.createTextNode("Add an Event"));
        $('#EventStuff').append(document.createElement("br"));
    $("<input/>").attr({type: "text", id: "eventTitle", placeholder : "Event Title"}).appendTo($('#EventStuff'));
    $("<input/>").attr({type: "text", id: "eventLoc", placeholder :"Event Location"}).appendTo($('#EventStuff'));
        $('#EventStuff').append(document.createElement("br"));
    $('#EventStuff').append(document.createTextNode("Date: "));
    $('#EventStuff').append(document.createElement("br"));

    var eventDay = $("<select></select>").attr("id", "startday");
    var startyear = $("<select></select>").attr("id", "startyear");
    var starthrs = $("<select></select>").attr("id", "starthrs");
    var startmins = $("<select></select>").attr("id", "startmins");
    var ampm = $("<select></select>").attr("id", "ampm");
    ampm.append("<option>AM</option>").attr("value", "AM");
    ampm.append("<option>PM</option>").attr("value", "PM");
    var add_btn = $("<button>Add Event </button>").attr("id", "add");
    
    var eventColor = $("<input/>").attr({type: "color", id: "eventCol", value: "#CD5C5C"});
    
    var eventType = $("<select></select>").attr("id", "eventType");
    $("<option>General</option>").attr("value", '1').appendTo(eventType);
    $("<option>Meeting</option>").attr("value", '2').appendTo(eventType);
    $("<option>Conference</option>").attr("value", '3').appendTo(eventType);
    $("<option>Presentation</option>").attr("value", '4').appendTo(eventType);
    $("<option>Lecture</option>").attr("value", '5').appendTo(eventType);
    $("<option>Party</option>").attr("value", '6').appendTo(eventType);
    $("<option>Birthday</option>").attr("value", '7').appendTo(eventType);
    $("<option>Other</option>").attr("value", '8').appendTo(eventType);
    
    //add the months to date selector, using code (i modified/tweaked it a bit) from stackoverflow.com/questions/22932253/angular-js-input-date-on-firefox and linked with date_and_time_event.js
    var eventMonth = $("<select></select>").attr("id", "startmonth");
    //make an array of option values and names:
    var months = [{name: "Jan", val: "01"},
                  {name: "Feb", val: "02"},
                  {name: "Mar", val: "03"},
                  {name: "Apr", val: "04"},
                  {name: "May", val: "05"},
                  {name: "Jun", val: "06"},
                  {name: "Jul", val: "07"},
                  {name: "Aug", val: "08"},
                  {name: "Sep", val: "09"},
                  {name: "Oct", val: "10"},
                  {name: "Nov", val: "11"},
                  {name: "Dec", val: "12"}];
    //load up the selector for the months:
    for(var m in months){
        var mm = $("<option>" + months[m].name + "</option>").attr("value", months[m].val);
        eventMonth.append(mm);
    }
    
    $('#EventStuff').append(eventDay);
    $('#EventStuff').append(eventMonth);
    $('#EventStuff').append(startyear);
    $('#EventStuff').append(document.createElement("br"));
    $('#EventStuff').append(document.createTextNode("Time: "));
    $('#EventStuff').append(document.createElement("br"));
    $('#EventStuff').append(starthrs);
    $('#EventStuff').append(startmins);
    $('#EventStuff').append(ampm);
    $('#EventStuff').append(document.createElement("br"));
    $('#EventStuff').append(document.createTextNode("Type of Event: "));
    $('#EventStuff').append(eventType);
    $('#EventStuff').append(document.createElement("br"));
    $('#EventStuff').append(document.createTextNode("Color: "));
    $('#EventStuff').append(eventColor);
    $('#EventStuff').append(document.createElement("br"));
    $('#EventStuff').append(add_btn);
    
    document.getElementById("add").addEventListener("click", addEvent, false);
    eventCreator();
}

function addEvent(){
    document.getElementById("err").innerHTML = "";
    var trydate = parseEvent();
    if(trydate === false){
        return;
    }
    var title = $("#eventTitle").val();
    if(!title){
        document.getElementById("err").innerHTML = "Your event must have a name";
        return;
    }
    var loc = $("#eventLoc").val();
    var month = trydate.getMonth() + 1;
    var year = trydate.getFullYear();
    var day = trydate.getDate();
    
    var full_date = year + "-" + month + "-" + day;
    var time = convertTime($("#starthrs").val(), $("#startmins").val(), $("#ampm").val());
    
    var col = $("#eventCol").val();
    col = col.slice(1);
    
   var e = document.getElementById("eventType");
   var type = e.options[e.selectedIndex].value;

    var dataString = "title=" + encodeURIComponent(title) + "&loc=" + encodeURIComponent(loc)+ "&date=" + encodeURIComponent(full_date)+ "&time=" + encodeURIComponent(time) + "&col=" + encodeURIComponent(col) +"&type=" + encodeURIComponent(type) +  "&tok=" + encodeURIComponent(tok);
    var xmlHttp = new XMLHttpRequest(); 
	xmlHttp.open("POST", "addEvent.php", true); 
	xmlHttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    
	xmlHttp.addEventListener("load", function(event){
		var jsonData = JSON.parse(event.target.responseText); 
		if(jsonData.success){
            tok = jsonData.tok;
            $("#EventStuff").empty();
            addEventForm();
            updateCalendar();
		}else{
			var err = document.getElementById("err");
			err.innerHTML = jsonData.message;
		}
	}, false); 
	xmlHttp.send(dataString);

}
//takes in string input in 12hr format and parses it into 24 hr format
function convertTime(h, m, x){
    hr = parseInt(h);
    min = parseInt(m);
    if(x == "PM" && hr >=1 && hr <=11){
        hr = hr + 12;
    }
    if( x == "AM" && hr == 12){
        hr = hr - 12;
    }
    if(min < 10){
        min = "0"+min;
    }
    if(hr < 10){
        mr = "0"+hr;
    }
    return (hr + ":" + min + ":00");
}

//takes in string input in 24hr format and parses it into 12 hr format
function convertTime12(h,m){
    var x;
    hr = parseInt(h);
    min = parseInt(m);
    if(hr<12 && min <=59){
        x = "AM";
    }
    if(hr>=12){
        hr = hr - 12;
        x = "PM";
    }
    if(hr === 0){
        hr = 12;
        x = "AM";
    }
    if(min < 10){
        min = "0" + min;
    }
    return (hr + ":" + min + x );
}
