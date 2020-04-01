<?php
session_start();

$key = $_GET['key'];
if($key != $_SESSION['regkey']) exit('KeyError');
$_SESSION['regkey'] = rand(1, 99999999999);

$mail = $_GET['mail'];

include './includes/connection.php';

$query = "SELECT 'User' FROM users WHERE Mail = '$mail' LIMIT 1";
mysqli_real_escape_string($con, $query);
$mysql = mysqli_query($con, $query);
$rows = mysqli_num_rows($mysql);
mysqli_free_result($mysql);
if($rows == 1) exit('exist');


$query = "SELECT RegTime FROM registering WHERE Mail = '$mail' LIMIT 1";
mysqli_real_escape_string($con, $query);
$mysql = mysqli_query($con, $query);
$rows = mysqli_num_rows($mysql);
$row = mysqli_fetch_row($mysql);
mysqli_free_result($mysql);
if($rows == 1)
{
	if($row[0] + 86400 > time()) exit('time');
	else
	{
		$query = "UPDATE registering SET RegTime = " . time() . ", RegKey = $key WHERE Mail = '$mail'";
		mysqli_real_escape_string($con, $query);
		$mysql = mysqli_query($con, $query);
		mail($mail,"Validarea contului","Buna ziua, ati cerut inregistrarea un cont pe http://www.laborator.ro folosind aceasta adresa de mail. \nPentru a valida aceasta cerere, click pe link-ul de mai jos si urmeaza instructiunile.\n http://www.laborator.ro/validate.php?mail=$mail&key=&key\n\n\nMultumim pentru inregistrare.");
		exit('succes');
	}
}

$query = "INSERT INTO registering (RegKey, Mail, RegTime) VALUES ($key, '$mail', " . time() . ")";
mysqli_real_escape_string($con, $query);
$mysql = mysqli_query($con, $query);
mail($mail,"Validarea contului","Buna ziua, ati cerut inregistrarea un cont pe http://www.laborator.ro folosind aceasta adresa de mail. \nPentru a valida aceasta cerere, click pe link-ul de mai jos si urmeaza instructiunile.\n http://www.laborator.ro/index.php?action=validate&mail=$mail&key=&key\n\n\nMultumim pentru inregistrare.");
echo('succes');
?>