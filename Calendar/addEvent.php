<?php

header("Content-Type: application/json"); // Since we are sending a JSON response here (not an HTML document), set the MIME Type to application/json
require("../../../CalendarSupport/database.php");
ini_set("session.cookie_httponly", 1);  //use HTTP Only option on cookies
session_start();

if(!isset($_SESSION['username']) || !isset($_SESSION['token'])){
    echo json_encode(array(
		"success" => false,
		"message" => "User not in session...",
		"tok" => 0
	));
	exit;
}

//Get all the variables first:
    $username = isset($_SESSION['username']) ? $_SESSION['username'] : "" ;
    $title = isset($_POST['title']) ? $_POST['title'] : "" ;
    $loc = isset($_POST['loc']) ? $_POST['loc'] : "" ;
	$col = isset($_POST['col']) ? $_POST['col'] : "" ;
	$col = trim($col);
    $time = isset($_POST['time']) ? $_POST['time'] : "" ;
	$type = isset($_POST['type']) ? $_POST['type'] : "" ;
    $date = isset($_POST['date']) ? $_POST['date'] : "" ;
    $tok = isset($_POST['tok']) ? $_POST['tok'] : "" ;
    
    if($_SESSION['token']  != $tok){
        echo json_encode(array(
		"success" => false,
        "message" => "Invalid session token.",
		"tok" => 0
	));
	exit;
    }
    
    $stmt = $mysqli->prepare("SELECT userID FROM Users WHERE username = ?");
    if(!$stmt){
        printf("Query Prep Failed: %s\n",$mysqli->errno, $mysqli->error);
        exit; 
    }
	$stmt->bind_param('s', $username);
	$stmt->execute();
    $stmt->bind_result($result);
    if( $stmt->fetch()){
        $id = $result;
    }
    else{
        echo json_encode(array(
		"success" => false,
		"message" => "Couldn't get ID",
		"tok" => 0
	));
	exit;
    }
	$stmt->close();
    
//prepare and add to database
    $stmt2 = $mysqli->prepare("INSERT INTO Events (userID, title, loc, date, time, color, type) VALUES (?, ?, ?, ?, ?, ?, ?)");
    if(!$stmt2){
        $msg = (htmlentities("Query Prep Failed: %s\n",$mysqli->errno, $mysqli->error));
        echo json_encode(array(
		"success" => false,
		"message" => $msg,
		"tok" => $_SESSION['token']
	));
	exit;
    }
    
    $stmt2->bind_param('isssssi', $id, $title, $loc, $date, $time, $col, $type);
    $stmt2->execute();
    $stmt2->close();
    $_SESSION['token']  = substr(md5(rand()), 0, 10);
    
    echo json_encode(array(
		"success" => true,
        "message" => "Event added",
        "tok" => $_SESSION['token']
	));
	exit;
    
?>