<?php

header("Content-Type: application/json"); // Since we are sending a JSON response here (not an HTML document), set the MIME Type to application/json
require("../../../CalendarSupport/database.php");
ini_set("session.cookie_httponly", 1);  //use HTTP Only option on cookies


// Check to see if the username and password are valid.  (You learned how to do this in Module 3.)
$valid = false;


$stmt5 = $mysqli->prepare("SELECT username, pwordHash FROM Users WHERE username=?");
        // Bind the parameter
    if(!$stmt5){
        printf("Query Prep Failed: %s\n",$mysqli->errno, $mysqli->error);
        exit;
    }
    
    $stmt5->bind_param('s', $username);
    
    $username = isset($_POST['username']) ? $_POST['username'] : "" ;
    $stmt5->execute();
     
    // Bind the results
    $stmt5->bind_result($username, $pword_hash);
    $stmt5->fetch();
    
    if(!$stmt5){
        echo "Wrong username";
    }
    $pwd_guess = isset($_POST['password']) ? $_POST['password'] : "" ; 
    if(password_verify($pwd_guess, $pword_hash)){
        // Login succeeded!
        $valid = true;
    }
	$stmt5->close();

if($valid){
	session_start();
	$_SESSION['username'] = $username;
	$_SESSION['token'] = substr(md5(rand()), 0, 10);
 
	echo json_encode(array(
		"success" => true,
		"tok" => $_SESSION['token']

	));
	exit;
}else{
	echo json_encode(array(
		"success" => false,
		"message" => "Incorrect Username or Password"
	));
	exit;
}

?>
