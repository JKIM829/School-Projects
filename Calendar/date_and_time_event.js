//This code for creating date and time input by creating select dropdowns is taken from http://stackoverflow.com/questions/22932253/angular-js-input-date-on-firefox
function eventCreator(){
for(var i = 1; i < 13; i++) {
	var s = i.toString();
	if(s.length == 1) {
		s = "0" + s; 
	}
	document.getElementById("starthrs").innerHTML += ("<option value='" + i + "'>" + s + "  </option>");
}
for(var j = 0; j < 60; j++) {
	var ss = j.toString();
	if(ss.length == 1) {
		ss = "0" + ss; 
	}
	document.getElementById("startmins").innerHTML += ("<option value='" + j + "'>" + ss + "  </option>");
}
for(var ii = 1; ii < 32; ii++) {
	var sss = i.toString();
	if(sss.length == 1) {
		sss = "0" +sss;
	}
	document.getElementById("startday").innerHTML += ("<option value='" + sss+ "'>" + ii + "  </option>");
}
for(var k = new Date().getFullYear(); k < (new Date().getFullYear() + 11); k++) {
	document.getElementById("startyear").innerHTML += ("<option value='" + k + "'>" + k + "  </option>");
}
}

function ddlValue(id) {
	var e = document.getElementById(id);
	var strUser = e.options[e.selectedIndex].value;
	return strUser;
}
// Validate date
function isDate(ExpiryDate) { // MM/DD/YYYY format
    var objDate,  // date object initialized from the ExpiryDate string 
        mSeconds, // ExpiryDate in milliseconds 
        day,      // day 
        month,    // month 
        year;     // year 
    // date length should be 10 characters (no more no less) 
    if (ExpiryDate.length !== 10) { 
        return false; 
    } 
    // third and sixth character should be '/' 
    if (ExpiryDate.substring(2, 3) !== '/' || ExpiryDate.substring(5, 6) !== '/') { 
        return false; 
    } 
    // extract month, day and year from the ExpiryDate (expected format is mm/dd/yyyy) 
    // subtraction will cast variables to integer implicitly (needed 
    // for !== comparing) 
    month = ExpiryDate.substring(0, 2) - 1 ; // because months in JS start from 0 
    day = ExpiryDate.substring(3, 5) - 0; 
    year = ExpiryDate.substring(6, 10) - 0; 
    // test year range 
    if (year < 1000 || year > 3000) { 
        return false; 
    } 
    // convert ExpiryDate to milliseconds 
    mSeconds = (new Date(year, month, day)).getTime(); 
    // initialize Date() object from calculated milliseconds 
    objDate = new Date(); 
    objDate.setTime(mSeconds); 
    // compare input date and parts from Date() object 
    // if difference exists then date isn't valid 
    if (objDate.getFullYear() !== year || 
        objDate.getMonth() !== month || 
        objDate.getDate() !== day) { 
        return false; 
    } 
    return objDate; 
}

//parseEvent() uses snippets of code from the original source.
function parseEvent(){
    parseInt(ddlValue("startday"));
	parseInt(ddlValue("startmonth"));
	parseInt(ddlValue("startyear"));
	parseInt(ddlValue("starthrs"));
	parseInt(ddlValue("startmins"));
    
    var tryDate = isDate(ddlValue("startmonth") + "/" + ddlValue("startday") + "/" + ddlValue("startyear"));
    //if tryDate === false, then not a valid date object                     
    if(tryDate===false) {
		document.getElementById("err").innerHTML = "Invalid date";
		return false;
	}
    else{
        return tryDate;
    }
}
