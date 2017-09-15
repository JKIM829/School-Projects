<?php
header("Content-Type: application/json"); // Since we are sending a JSON response here (not an HTML document), set the MIME Type to application/json
require("../../../CalendarSupport/database.php");
ini_set("session.cookie_httponly", 1);  //use HTTP Only option on cookies
session_start();

if(!isset($_SESSION['username']) || !isset($_SESSION['token'])){
    echo json_encode(array(
		"success" => false,
		"message" => "User not in session..."
	));
	exit;
}

//Get all the variables first:
    $username = isset($_SESSION['username']) ? $_SESSION['username'] : "" ;
    $month = isset($_POST['month']) ? $_POST['month'] : "" ;
    $tok = isset($_POST['tok']) ? $_POST['tok'] : "" ;
    $year = isset($_POST['year']) ? $_POST['year'] : "" ;
    
    if($_SESSION['token']  != $tok){
        echo json_encode(array(
		"success" => false,
        "message" => "Invalid session token."
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
		"message" => "Couldn't get ID"
	));
	exit;
    }
	$stmt->close();
    
    //get events by USERID
    $stmt2 = $mysqli->prepare("SELECT * FROM Events WHERE Year(date) = ? and Month(date) = ? and userID = ? ORDER BY date,time DESC ");
	
    if(!$stmt2){
        $msg = (htmlentities("Query Prep Failed: %s\n",$mysqli->errno, $mysqli->error));
        echo json_encode(array(
		"success" => false,
		"message" => $msg,
		'events' => false
	));
	exit;
    }
    
    $stmt2->bind_param('iii', $year, $month, $id);
    $stmt2->execute();	
    //code references http://stackoverflow.com/questions/6281963/how-to-build-a-json-array-from-mysql-database
    $rows = array();
    $result = $stmt2->get_result();
    while($r = $result->fetch_assoc()){
        $rows['events'][] = $r;
    }
	$stmt2->close();
	
	if($rows == null){
		$rows['events'] = false;
	}
	
	$_SESSION['token'] = substr(md5(rand()), 0, 10);
	echo json_encode(array(
		"success" => true,
        "tok" => $_SESSION['token'],
        'events' => $rows['events']
	));
	exit;
	
?>