var tok = 0;
//AGHHHH SHOULD HAVE USED JQUERY 
function loginAjax() {
	var username = document.getElementById("username").value; // Get the username from the form
	var password = document.getElementById("password").value; // Get the password from the form
 
	// Make a URL-encoded string for passing POST data:
	var dataString = "username=" + encodeURIComponent(username) + "&password=" + encodeURIComponent(password);
 
	var xmlHttp = new XMLHttpRequest(); // Initialize our XMLHttpRequest instance
	xmlHttp.open("POST", "login.php", true); // Starting a POST request
    
	xmlHttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded"); // It's easy to forget this line for POST requests
    
	xmlHttp.addEventListener("load", function(event){
		var jsonData = JSON.parse(event.target.responseText); // parse the JSON into a JavaScript object
		if(jsonData.success){  // in PHP, this was the "success" key in the associative array; in JavaScript, it's the .success property of jsonData
			tok = jsonData.tok;
            refresh();
		}else{
			var err = document.getElementById("err");
			err.innerHTML = jsonData.message;
		}
	}, false); // Bind the callback to the load event
	xmlHttp.send(dataString); // Send the data
}

function signupAjax() {
	var username1 = document.getElementById("username1").value; // Get the username from the form
	var password1 = document.getElementById("password1").value; // Get the password from the form
    var first = document.getElementById("first").value;
    var last = document.getElementById("last").value;
    var password_ver = document.getElementById("password1_ver").value;
 
	// Make a URL-encoded string for passing POST data:
	var dataString1 = "username=" + encodeURIComponent(username1) + "&password=" + encodeURIComponent(password1) + "&password1_ver=" + encodeURIComponent(password_ver)  + "&first=" + encodeURIComponent(first) + "&last=" + encodeURIComponent(last);
 
	var xmlHttp1 = new XMLHttpRequest(); // Initialize our XMLHttpRequest instance
	xmlHttp1.open("POST", "signUp.php", true); // Starting a POST request
    
	xmlHttp1.setRequestHeader("Content-Type", "application/x-www-form-urlencoded"); // It's easy to forget this line for POST requests
    
	xmlHttp1.addEventListener("load", function(event){
		var jsonData1 = JSON.parse(event.target.responseText); // parse the JSON into a JavaScript object
		if(jsonData1.success){  // in PHP, this was the "success" key in the associative array; in JavaScript, it's the .success property of jsonData
			tok = jsonData1.tok;
            refresh();
		}else{
			var err = document.getElementById("err");
			err.innerHTML = jsonData1.message;
		}
	}, false); // Bind the callback to the load event
	xmlHttp1.send(dataString1); // Send the data
}

function logOutUser(){
	
	var xmlHttp2 = new XMLHttpRequest(); // Initialize our XMLHttpRequest instance
	xmlHttp2.open("GET", "logout.php", true); // Starting a POST request
    
	xmlHttp2.setRequestHeader("Content-Type", "application/x-www-form-urlencoded"); // It's easy to forget this line for POST requests
    
	xmlHttp2.addEventListener("load", function(event){
		var jsonData2 = JSON.parse(event.target.responseText); // parse the JSON into a JavaScript object
		if(jsonData2.success){  // in PHP, this was the "success" key in the associative array; in JavaScript, it's the .success property of jsonData
			tok = 0;
			refresh();
		}else{
			alert("Something went wrong:  " + jsonData2.message);
			var err = document.getElementById("err");
			err.innerHTML = jsonData2.message;
		}
	}, false); // Bind the callback to the load event
	xmlHttp2.send(null); 
}

function checkUser(){
	var check = getUser();
	if(check === false){	//no user signed in
		loadPage();
	}
	else{
		loadUser();
	}		
}


document.addEventListener("DOMContentLoaded", initialize, false);

function initialize(){
	loadPage();    //do sidebar stuff
	displayCalendar();	//print out calendar(basic/non event one)
    document.getElementById("next").addEventListener("click", nextMonth, false);
	document.getElementById("prev").addEventListener("click", prevMonth, false);
}

function refresh(){
    //clear the nodes in the login/signup sidebar	
	$("#LoginForm").children().each(function(){$(this).empty();});
	$("#SignUp").children().each(function(){$(this).empty();});
	$("#Logged").children().each(function(){$(this).empty();});
	
	$("#err").empty();
	checkUser();    //do sidebar stuff
	displayCalendar();	
}

function loadPage(){	//this loads the sidebar !!SHOULD HAVE USED JQUERY SMH!!
	var log = document.getElementById("LoginForm");
    var sign = document.getElementById("SignUp");
		
        //nobody's signed in yet, so create these nodes for login
        var titleL = log.children[0];
        titleL.appendChild(document.createTextNode("Log In"));
        
        var unameField = log.children[1];
        var uname = document.createElement("input");
        uname.setAttribute("type", "text");
        uname.setAttribute("id", "username");
        uname.setAttribute("placeholder", "Username");
        unameField.appendChild(uname);
        
        var pwordField = log.children[2];
        var pword = document.createElement("input");
        pword.setAttribute("type", "password");
        pword.setAttribute("id", "password");
        pword.setAttribute("placeholder", "Password");
        pwordField.appendChild(pword);
        
        var btnField = log.children[3];
        var btn = document.createElement("BUTTON");
        btn.setAttribute("id", "login_btn");
        btn.appendChild(document.createTextNode("Log In"));
        btnField.appendChild(btn);
        btnField.appendChild(document.createElement("br"));
        btnField.appendChild(document.createElement("br"));
        document.getElementById("login_btn").addEventListener("click", loginAjax, false); // Bind the AJAX call to button click
        
        //create nodes for signup
        var titleS = sign.children[0];
        titleS.appendChild(document.createTextNode("Sign Up"));
        
        var infoField = sign.children[1];
        var u = document.createElement("input");
        u.setAttribute("type", "text");
        u.setAttribute("id", "username1");
        u.setAttribute("placeholder", "Username");
        infoField.appendChild(u);
        infoField.appendChild(document.createElement("br"));
        var p = document.createElement("input");
        p.setAttribute("type", "password");
        p.setAttribute("id", "password1");
        p.setAttribute("placeholder", "Password");
        infoField.appendChild(p);
        infoField.appendChild(document.createElement("br"));
        var p_ver = document.createElement("input");
        p_ver.setAttribute("type", "password");
        p_ver.setAttribute("id", "password1_ver");
        p_ver.setAttribute("placeholder", "Verify Password");
        infoField.appendChild(p_ver);
        infoField.appendChild(document.createElement("br"));
        var first = document.createElement("input");
        first.setAttribute("type", "text");
        first.setAttribute("id", "first");
        first.setAttribute("placeholder", "First Name");
        infoField.appendChild(first);
        infoField.appendChild(document.createElement("br"));
        var last = document.createElement("input");
        last.setAttribute("type", "text");
        last.setAttribute("id", "last");
        last.setAttribute("placeholder", "Last Name");
        infoField.appendChild(last);
        infoField.appendChild(document.createElement("br"));

        var btnField1 = sign.children[2];
        var btn1 = document.createElement("BUTTON");
        btn1.setAttribute("id", "sign_up");
        btn1.appendChild(document.createTextNode("Sign Up"));
        btnField1.appendChild(btn1);
        
        document.getElementById("sign_up").addEventListener("click", signupAjax, false); // Bind the AJAX call to button click
}

function loadUser(){
	var btn = document.createElement("BUTTON");
    btn.setAttribute("id", "logout");
    btn.appendChild(document.createTextNode("Log Out"));
	$(".LogOut").append(btn);
    document.getElementById("logout").addEventListener("click", logOutUser, false); // Bind the AJAX call to button click
	addEventForm();
	var user = getUser();
	var title = document.createTextNode("Welcome, " + user);
	$('#UserStuff').append(title);
	}

function getUser(){
	$.ajaxSetup({
		async:false
	});
	$.ajax({
		type: "POST",
		data: "tok=" + encodeURIComponent(tok),	//send the token to verify it's the same as the session token
		dataType: "json",
		url: "checkUser.php",
		error: function(){
			result = "no user";
		},
		success:function(data){
			if(data.success){
			result = data.user;
			tok = data.tok;
			}
			else{
			err = data.message;
			result = false;
			}
		}
		
	});
	$.ajaxSetup({
		async:true
	});
	
	return result;
}

