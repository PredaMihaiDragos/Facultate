<?php
session_start();

include 'connection.php';

$key = $_POST['key'];

if($_SESSION['key'] != $key) exit('wrongKey');

$nume = mysqli_real_escape_string($con, $_POST['nume']);
$prenume = mysqli_real_escape_string($con, $_POST['prenume']);
$cnp = mysqli_real_escape_string($con, $_POST['cnp']);
$trim = mysqli_real_escape_string($con, $_POST['trim']);
$mail = mysqli_real_escape_string($con, $_POST['mail']);
$phone = mysqli_real_escape_string($con, $_POST['phone']);
$liber = mysqli_real_escape_string($con, $_POST['liber']);
$alte = mysqli_real_escape_string($con, $_POST['alte']);
$time = time();

mysqli_query($con,"INSERT INTO programari (Code, Nume, Prenume, CNP, Phone, Mail, Trimitere, Liber, Alte, Timestamp) 
										   VALUES ($key, '$nume', '$prenume', '$cnp', '$phone', '$mail', '$trim', '$liber', '$alte', '$time')");

?>