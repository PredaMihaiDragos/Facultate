<?php
session_start();

$pass = $_GET['pass'];
$code = $_GET['code'];

if($code != $_SESSION['security_code']) exit('wrongCode');

include './includes/pass.php';
if($pass != $adminpass) exit('wrongPass');

echo 'succes';
$_SESSION['admin'] = 'parola';

?>