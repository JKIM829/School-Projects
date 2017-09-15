<?php
//this script checks whether a user is already set, and returns true/false to AJAX

header("Content-Type: application/json"); // Since we are sending a JSON response here (not an HTML document), set the MIME Type to application/json
ini_set("session.cookie_httponly", 1);  //use HTTP Only option on cookies

session_start();


if(isset($_SESSION['username']) && isset($_SESSION['token'])){
	$trytoken = isset($_POST['tok']) ? $_POST['tok'] : "" ;
	if($trytoken == $_SESSION['token'] ){	//if the session token variable is the same as the passed token variable
		$_SESSION['token']  = substr(md5(rand()), 0, 10);
		echo json_encode(array(
			"success" => true,
			"tok" => $_SESSION['token'],
			"user" => $_SESSION["username"]
		));
		exit;	
	}
	else{
		 echo json_encode(array(
		"success" => false,
		"message" => "Not Logged In."
	));
		exit;
	}
    
}

else{
    echo json_encode(array(
		"success" => false,
		"message" => "Not Logged In."
	));
	exit;
}


?>