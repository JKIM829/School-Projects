var d = new Date();
var cur_month = d.getMonth();
var cur_date = d.getDay();
var cur_year = d.getFullYear();

var months = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"];
var weekdays = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"];

var currentMonth = new Month(cur_year, cur_month);

var header = document.createElement("TR");
	header.setAttribute("class", "header");
	for(var i = 0; i< 7; ++i){
		var d = document.createElement('TD');
		d.setAttribute("class", "header");
		d.appendChild(document.createTextNode(weekdays[i]));
		header.appendChild(d);
	}
	
function displayCalendar(){
    $("#calendar").empty();  //get rid of the previous calendar (if it exists)
	
    var calTitle = document.getElementById("CalendarTitle");
    var thisMonth = months[currentMonth.month] + " " + currentMonth.year;
    calTitle.innerHTML = thisMonth;
    
    var myTableDiv = document.getElementById("calendar");
    var table = document.createElement("TABLE");
	table.appendChild(header);
    var tableBody = document.createElement('TBODY');
    table.appendChild(tableBody);
    
    var weeks = currentMonth.getWeeks();
    
    var overflow = 0;
    var tr = document.createElement('TR');
	
	var event_arr = getEvents();	//this function, found in showEvents.js checks if there are events (and thus, check whether there's a user in the first place, passing the csrf token to check)
		
	for(var w in weeks){
		var days = weeks[w].getDates();
		for(var d in days){
            if((overflow%7)===0){
                tr = document.createElement('TR');
                tableBody.appendChild(tr);
            }
            var dd = days[d].getDay();
            //use a <div> inside <td> to customize the cell
            var entry = document.createElement("div");
            entry.setAttribute('class', 'dateObj');
            var td = document.createElement('TD');
			var cell = document.createElement("div");
            cell.setAttribute("class", "cal_entry");
			
            if(days[d].getMonth()!= currentMonth.month){
               entry.appendChild(document.createTextNode(""));
               cell.appendChild(entry);
			   td.appendChild(cell);
               tr.appendChild(td);
               ++overflow;
               continue;
            }
           else if(dd == (overflow%7)){	//creating non-blank cell entries for the calendar
				cell.appendChild(entryCreator(days[d], event_arr));
				td.appendChild(cell);
				tr.appendChild(td);
               ++overflow;
            }
           else{
               entry.appendChild(document.createTextNode(""));
               cell.appendChild(entry);
			   td.appendChild(cell);
               tr.appendChild(td);
               ++overflow;
            }
		}
	}
	
    myTableDiv.appendChild(table);
	
	$(document).ready(function(){
      if(tok!==0){
		$(".jq-dropdown-panel").children().each(function(){$(this).empty();});
		createDropdwn();
		load_Dialog();
	  }
  });
	
}

function updateCalendar(){
    //update the calendar, whenever something on page changes.
    thisMonth = months[currentMonth.month] + " " + currentMonth.year;
    displayCalendar();
}

function nextMonth(){
    currentMonth = currentMonth.nextMonth(); // Previous month would be currentMonth.prevMonth()
	updateCalendar(); // Whenever the month is updated, we'll need to re-render the calendar in HTML
}

function prevMonth(){
    currentMonth = currentMonth.prevMonth(); // Previous month would be currentMonth.prevMonth()
	updateCalendar(); // Whenever the month is updated, we'll need to re-render the calendar in HTML
}

function entryCreator(date, ev_arr){
	var entry = document.createElement("div");
		entry.setAttribute('class', 'dateObj');
		var dateText = document.createElement("b");
		dateText.setAttribute("class","dateObj");
		dateText.appendChild(document.createTextNode((date.getDate())));
		entry.appendChild(dateText);
		
	if(ev_arr === false){	//if the token is 0, then no users are signed in
		return entry;
	}
	else{
	for(var i = ev_arr.length - 1; i >= 0; i--){
		if(compareDates(ev_arr[i].date, date)){
			var time = parseTime(ev_arr[i].time);
			var Entry = document.createElement("a");
			Entry.setAttribute('class', 'Event');
			Entry.setAttribute('href', '#');
			Entry.style.color = "#" + ev_arr[i].color;
			Entry.style.backgroundColor = types[ev_arr[i].type-1].col;
			Entry.appendChild(document.createTextNode(time + "  " + ev_arr[i].title));
			var dialog = dialogCreator(ev_arr[i]);
			entry.appendChild(Entry);
			entry.appendChild(dialog);
			
			ev_arr.splice(i,1);	//get rid of date
		}
	}
	}
	return entry;
}

function dialogCreator(obj){
	var ev = document.createElement("div");
	ev.setAttribute("class", "dialog");
	ev.setAttribute("title", obj.title);
	ev.setAttribute("value", obj.eventID);
	var loc = obj.loc;
	if(obj.loc === ""){
		loc = "Not Specified";
	}
	var t = parseTime(obj.time);
	ev.appendChild(document.createElement("p").appendChild(document.createTextNode("Where: " + loc)));
	ev.appendChild(document.createElement("br"));
	ev.appendChild(document.createElement("p").appendChild(document.createTextNode("When: " + t + " " + obj.date)));
	ev.appendChild(document.createElement("br"));
	
	ev.appendChild(document.createElement("p").appendChild(document.createTextNode("Type of Event: " +types[obj.type-1].name)));
	return ev;	
}

function compareDates(string_date, d){
	var dateParts = string_date.split('-');
	var y = dateParts[0];
	var m = dateParts[1]-1;
	var day = dateParts[2];
	var dd = new Date(y,m,day);
	if(dd.getYear() == d.getYear()){
		if(dd.getMonth() == d.getMonth()){
			if(dd.getDate() == d.getDate()){
				return true;
			}
		}
	}
	else{
		return false;
	}
}

function parseTime(t){
	var timeparts = t.split(':');
	var h = timeparts[0];
	var m = timeparts[1];
	return convertTime12(h,m);
}

function parseType(i){
	switch(i){
		case 1:
			return "#FFFFFF";
		case 2:
			return "#E0FFFF";
		case 3:
			return "#FFE4E1";
		case 4:
			return "#FFEFD5";
		case 5:
			return "#D8BFD8";
		case 6:
			return "#90EE90";
		case 7:
			return "#B0C4DE";
		case 8:
			return "#dfecdf";
	}
}

var types = 	 [{name: "General", val: 1, col : "#FFFFFF" },
                  {name: "Meeting", val: 2, col : "#ccffff" },
                  {name: "Conference", val: 3, col : "#e6d2f9"},
                  {name: "Presentation", val: 4, col : "#FFEFD5"},
                  {name: "Lecture", val: 5, col : "#D8BFD8"},
                  {name: "Party", val: 6, col:"#d3f8d3" },
                  {name: "Birthday", val: 7, col:"#B0C4DE"},
                  {name: "Other", val: 8, col:"#ffffb3"},
				  {name: "Error", val: 10, col:"#ff0066"},
					 {name: "Error2", val: 0, col:"#ff0066"}
                 ];

