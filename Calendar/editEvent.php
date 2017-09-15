<?php
header("Content-Type: application/json"); // Since we are sending a JSON response here (not an HTML document), set the MIME Type to application/json
require("../../../CalendarSupport/database.php");
ini_set("session.cookie_httponly", 1);  //use HTTP Only option on cookies
session_start();

if(!isset($_SESSION['username']) || !isset($_SESSION['token'])){
    echo json_encode(array(
		"success" => false,
		"tok" => 0,
		"message" => "User not in session..."
	));
	exit;
}

//Get all the variables first:
	$username = isset($_SESSION['username']) ? $_SESSION['username'] : "" ;
	$data = array();
    $data['title'] = isset($_POST['title']) ? $_POST['title'] : "" ;
    $data['loc'] = isset($_POST['loc']) ? $_POST['loc'] : "" ;
    $data['time'] = isset($_POST['time']) ? $_POST['time'] : "" ;
    $data['date'] = isset($_POST['date']) ? $_POST['date'] : "" ;
	$data['color'] = isset($_POST['col']) ? $_POST['col'] : "" ;
	$data['type'] = isset($_POST['type']) ? $_POST['type'] : "";
	
    $tok = isset($_POST['tok']) ? $_POST['tok'] : "" ;
    $eventID = isset($_POST['eventID']) ? $_POST['eventID'] : "" ;
	
    if($_SESSION['token']  != $tok){
        echo json_encode(array(
		"success" => false,
		"tok" => 0,
        "message" => "Invalid session token."
	));
	exit;
    }
	
	
	//dynamically prepare sql statment:
	$sqlstring = "UPDATE Events SET ";
	$count = 0;
	$bind_param = "";
	$param = array();
	
	foreach($data as $x => $x_value){
		if($x_value != ""){
			if($count > 0){
			$sqlstring .= ", ". $x . " = ?";
			
			if($x == "type"){
				$bind_param.='i';
			}
			else{
				$bind_param.='s';
			}
			$param[$count] = $x_value;
			}
			
			else{
			$sqlstring .= $x . " = ?";
			if($x == "type"){
				$bind_param.='i';
			}
			else{
				$bind_param.='s';
			}
			$param[$count] = $x_value;
			}
			++$count;
		}
	}
	
	
	$sqlstring .= " WHERE eventID = ?";
    $bind_param.= 'i';

    $stmt = $mysqli->prepare($sqlstring);
    if(!$stmt){
        printf("Query Prep Failed: %s\n",$mysqli->errno, $mysqli->error);
        exit; 
    }
	if($count == 1){
		$stmt->bind_param($bind_param, $param[0], $eventID);
	}
	if($count == 2){
		$stmt->bind_param($bind_param, $param[0],$param[1], $eventID);
	}
	if($count == 3){
		$stmt->bind_param($bind_param, $param[0],$param[1], $param[2], $eventID);
	}
	if($count == 4){
		$stmt->bind_param($bind_param, $param[0],$param[1], $param[2],$param[3], $eventID);
	}
	if($count == 5){
		$stmt->bind_param($bind_param, $param[0],$param[1], $param[2],$param[3], $param[4], $eventID);
	}
	if($count == 6){
		$stmt->bind_param($bind_param, $param[0],$param[1], $param[2],$param[3], $param[4], $param[5], $eventID);
	}
	
	$stmt->execute();
    if( !$stmt){
        echo json_encode(array(
		"success" => false,
		"tok" => $_SESSION['token'],
		"message" => $sqlstring . " " . $bind_param . " " . implode(" ", $param)
	));
	exit;
    }
	$stmt->close();
    
   
	$_SESSION['token'] = substr(md5(rand()), 0, 10);
	echo json_encode(array(
		"success" => true,
        "tok" => $_SESSION['token'],
        "message" => $sqlstring . " " . $bind_param . " " . implode(" ",$param)
	));
	exit;
	
?>