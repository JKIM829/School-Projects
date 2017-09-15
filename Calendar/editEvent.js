function editEvent(eventID){
    
    var t = $("#changeTitle").val();
    var l = $("#changeLoc").val();
    var time2 = $("#changeTime").val();
    var d = $("#changeDate").val();
    var c = $("#changeCol").val();
    c =  c.slice(1);
    if(c == "ffffff"){
            c ="";
    }
    var type = $("#changeType").val();
    if(type == 10){
        type = "";
    }
    
    if(d !== ""){
    d = parseDate(d);
    if (d === false){
         $("#editerr").html ( "Error: invalid date entered");
        return false;
        }
    }
    if(time2!==""){
    time2 = parseTime2(time2);
    if(time2 === false){
        $("#editerr").html( "Error: invalid time entered");
        return false;
        }
    }
    if(t === "" && l ==="" && time2==="" && d ==="" && c ==="" && type ===""){
        $("#editerr").html( "You have to change at least 1 field to edit an event");
        return false;
    }
    
var dataString = "eventID=" + encodeURIComponent(eventID) + "&tok=" + encodeURIComponent(tok)+ "&title=" + encodeURIComponent(t)+ "&loc=" + encodeURIComponent(l);
dataString += "&time=" + encodeURIComponent(time2) + "&col=" + encodeURIComponent(c)+ "&date=" + encodeURIComponent(d)+ "&type=" + encodeURIComponent(type);


var result;

$.ajaxSetup({
		async:false
	});
	$.ajax({
		type: "POST",
		url: "editEvent.php",
        data: dataString,
        dataType: "json",
		success:function(data){
            if(data.success){
                tok = data.tok;
                result = true;
            }
            else{
                console.log(data.message);
            }
		},
        error: function(data){
            console.log(data.message);
            result = false;
        }
	});
	$.ajaxSetup({
		async:true
	});
    
    if(result===null){
		result = false;
	}
    return result;
}
//This function creates the form inside the dropdown box that opens when you try to edit an event
function createDropdwn(){
    var eventType = $("<select></select>").attr("id", "changeType");
    $("<option>No Change</option>").attr("value", '10').appendTo(eventType);
    $("<option>General</option>").attr("value", '1').appendTo(eventType);
    $("<option>Meeting</option>").attr("value", '2').appendTo(eventType);
    $("<option>Conference</option>").attr("value", '3').appendTo(eventType);
    $("<option>Presentation</option>").attr("value", '4').appendTo(eventType);
    $("<option>Lecture</option>").attr("value", '5').appendTo(eventType);
    $("<option>Party</option>").attr("value", '6').appendTo(eventType);
    $("<option>Birthday</option>").attr("value", '7').appendTo(eventType);
    $("<option>Other</option>").attr("value", '8').appendTo(eventType);
    
    
    var d3 = $("<form></form>").attr("id", "EditEvent").appendTo($(".jq-dropdown-panel"));
    $("<input/>").attr({type : "text", id : "changeTitle", placeholder :"Title"}).appendTo(d3);
    d3.append($("<br>"));
    $("<input/>").attr({type : "text", id : "changeLoc", placeholder: "Location"}).appendTo(d3);
    d3.append($("<br>"));
    $("<input/>").attr({type : "text", id : "changeTime", placeholder : "Time e.g. 1:30AM" , maxlength: 7}).appendTo(d3);
    d3.append($("<br>"));
    $("<input/>").attr({type : "text", id : "changeDate", placeholder : "Date MM/DD/YYYY" , maxlength: 10}).appendTo(d3);
    d3.append($("<br>"));
    d3.append(document.createTextNode("Event Type: "));
    d3.append(eventType);
    d3.append($("<br>"));
    d3.append(document.createTextNode("Color: "));
    $("<input/>").attr({type : "color", id : "changeCol", value : "#FFFFFF"}).appendTo(d3);
    d3.append($("<br>"));
    $("<div></div>").attr({class: "errorMSG", id: "editerr"}).appendTo(d3);
    $("<button>Edit Event</button>").attr('id', 'edit').appendTo(d3);
    
    $("#edit").click(function(){
		var id = $("#edit").val();
		if( editEvent(id)){
			$("#jq-dropdown-1").jqDropdown('hide');
			$(".ui-dialog-content").dialog("close");
			updateCalendar();
		}
	});
}

function parseTime2(t){
    var timeparts = t.match(/^(\d{1,2})\:(\d{2})(am|pm|AM|PM)$/);
    if(timeparts !== null){
    var h = +timeparts[1], m = +timeparts[2], ampm = timeparts[3];
    if(parseInt(h) > 12 || parseInt(m)>59){
        return false;
        }
        return convertTime(h,m,ampm);
    }
	return false;
}
//This function found from http://stackoverflow.com/questions/7582828/how-to-check-if-a-string-is-a-legal-dd-mm-yyyy-date
function parseDate(str) {
  var t = str.match(/^(\d{1,2})\/(\d{1,2})\/(\d{4})$/);
  if(t !== null){
    var m = +t[1], d = +t[2], y = +t[3];
    var date = new Date(y, m - 1, d);
    if(date.getFullYear() === y && date.getMonth() === m - 1) {
        var full_date = y + "-" + m + "-" + d;
      return full_date;   
    }
  }
  return false;
}