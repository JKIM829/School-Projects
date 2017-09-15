<?php
header("Content-Type: application/json"); // Since we are sending a JSON response here (not an HTML document), set the MIME Type to application/json
require("../../../CalendarSupport/database.php");
ini_set("session.cookie_httponly", 1);  //use HTTP Only option on cookies

// Check to see if the username and password are valid.  
$valid = false;

//Get all the variables first:
    $username = isset($_POST['username']) ? $_POST['username'] : "" ;
    $pword = isset($_POST['password']) ? $_POST['password'] : "" ;
    $pword_ver = isset($_POST['password1_ver']) ? $_POST['password1_ver'] : "" ;
    $first = isset($_POST['first']) ? $_POST['first'] : "" ;
    $last = isset($_POST['last']) ? $_POST['last'] : "" ;
    
//Make sure information is valid:

    if(!preg_match('/^[a-zA-Z0-9]{3,16}$/', $username) ){
        echo json_encode(array(
		"success" => false,
		"message" => "Invalid Username. Must be 3 to 16 characters or numbers long, with no spaces."
	));
        exit;
    }
    
    if(!preg_match('/^[a-zA-Z]{2,45}$/', $first)){
       echo json_encode(array(
		"success" => false,
		"message" => "Invalid first name. Must be 2 to 45 characters long, with no spaces."
        ));
        exit;
    }
    
    if(!preg_match('/^[a-zA-Z]{2,45}$/', $last)){
       echo json_encode(array(
		"success" => false,
		"message" => "Invalid first name. Must be 2 to 45 characters long, with no spaces."
        ));
        exit;
    }
    if(!preg_match('/^[a-zA-Z0-9]{8,45}$/', $pword)){
       echo json_encode(array(
		"success" => false,
		"message" => "Invalid password. Must be 8 to 45 chararcters long, using alphanumerical symbols without spaces."
        ));
        exit;
    }
    if($pword!= $pword_ver){
        echo json_encode(array(
		"success" => false,
		"message" => "Password verification does not match."
        ));
        exit;
    }
    
    //make sure username is unique:
    $stmt = $mysqli->prepare("SELECT username FROM Users WHERE username = ?");
    if(!$stmt){
        printf("Query Prep Failed: %s\n",$mysqli->errno, $mysqli->error);
        exit; 
    }
	$stmt->bind_param('s', $username);
	$stmt->execute();
	if($stmt->fetch()){
		echo json_encode(array(
		"success" => false,
		"message" => "That username has already been claimed."
        ));
        exit; 
	}
	$stmt->close();
    
    //then, store password safely
    $hash = password_hash($pword, PASSWORD_DEFAULT);
    
    $stmt2 = $mysqli->prepare("INSERT INTO Users (username, pwordHash, first_name, last_name) VALUES (?, ?, ?, ?)");
    if(!$stmt2){
        printf("Query Prep Failed: %s\n",$mysqli->errno, $mysqli->error);
        exit;
    }
    $stmt2->bind_param('ssss', $username, $hash, $first, $last);
    $stmt2->execute();
    $stmt2->close();
    

if($stmt2){
    
	session_start();
	
    $_SESSION['username'] = $username;
    $_SESSION['token']  = substr(md5(rand()), 0, 10);
 
	echo json_encode(array(
		"success" => true,
		"tok" => $_SESSION['token']
	));
	exit;
}
else{
	echo json_encode(array(
		"success" => false,
		"message" => "Could not create new user..."
	));
	exit;
}

?>