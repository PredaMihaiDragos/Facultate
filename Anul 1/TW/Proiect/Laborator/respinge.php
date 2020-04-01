<?php
session_start();

include './includes/connection.php';
include './includes/pass.php';
if($_SESSION['admin'] != $adminpass) exit();

$code = (int)$_GET['code'];

mysqli_query($con, "UPDATE programari SET Accept = 0 WHERE Code = " . $code);

?>