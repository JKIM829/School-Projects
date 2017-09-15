<?php
    $mysqli = new mysqli("localhost", "phpuser", "phppassword", "CalendarUsers");
    
    if($mysqli->connect_errno){
    printf("Connection Failed: $s\n", $mysqli->connect_error);
    exit;
    }
    
    
?>