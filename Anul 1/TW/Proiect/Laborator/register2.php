<?php

$mail = $_GET['mail'];
$key = $_GET['key'];
$user = $_GET['user'];
$pass = $_GET['pass'];

include './includes/connection.php';

$query = "SELECT User FROM users WHERE Mail = '$mail' LIMIT 1";
mysqli_real_escape_string($con, $query);
$mysql = mysqli_query($con, $query) or die(mysqli_error($con));
$rows = mysqli_num_rows($mysql);
if($rows == 1) exit('userExist');

$query = "DELETE FROM registering WHERE Mail = '$mail' AND RegKey = '$key' LIMIT 1";
mysqli_real_escape_string($con, $query);
mysqli_query($con, $query);
$rows = mysqli_affected_rows($con);
if($rows != 1) exit('Hacking attempt');

$query = "INSERT INTO users (User, Password, Mail) VALUES('$user', '$pass', '$mail')";
mysqli_real_escape_string($con, $query);
mysqli_query($con, $query) or die(mysqli_error($con));
$rows = mysqli_affected_rows($con);
if($rows == 1) echo('succes');
else echo('error');



?>