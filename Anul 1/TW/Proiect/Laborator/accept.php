<?php
session_start();

include './includes/pass.php';
if($_SESSION['admin'] != $adminpass) exit();

include './includes/connection.php';
$code = (int)$_GET['code'];

mysqli_query($con, "UPDATE programari SET Accept = 1 WHERE Code = " . $code);

$time = $_GET['hour'];
$date = $_GET['date'];
$alte = $_GET['alte'];

?>