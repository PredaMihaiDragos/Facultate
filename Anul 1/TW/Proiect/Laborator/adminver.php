<?php
session_start();
error_reporting(0);
include './includes/pass.php';
if($_GET['pass'] == $adminpass)
{
	$_SESSION['admin'] = $adminpass;
	header('Location: admin.php');
	exit();
}

if($_SESSION['admin'] == $adminpass)
{
	header( 'Location: admin.php' ) ;
	exit;
}

?>

<html>
<head>

<script>

function refresh()
{
	document.getElementById('captchaImg').src = 'captcha.php';
}

function submit()
{
	var pass = document.getElementById('pass').value;
	var code = document.getElementById('captcha').value;
	var xmlhttp;
	if(window.XMLHttpRequest) xmlhttp=new XMLHttpRequest();
	else xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	xmlhttp.open("GET","passcheck.php?pass=" + pass + "&code=" + code,false);
	xmlhttp.send();
	if (xmlhttp.readyState==4 && xmlhttp.status==200)
	{
		var response = xmlhttp.responseText;
		if(response == 'succes') 
		{
			document.getElementById('passInput').value = pass;
			document.getElementById('passForm').submit();
		}
		else if(response == 'wrongCode') 
		{
			alert('Security code error.');
			refresh();
			document.getElementById('pass').value = '';
			document.getElementById('captcha').value = '';
		}
		else if(response == 'wrongPass') 
		{
			alert('Password error.');
			refresh();
			document.getElementById('pass').value = '';
			document.getElementById('captcha').value = '';
		}
	}
}
</script>

</head>
<body>

<center>
<br><br><br><br><br><br>
	Password: &nbsp;&nbsp;<input type = 'password' id = 'pass'></input><br><br>
	Introdu codul: <input type = 'text' id = 'captcha'></input><img id = 'captchaImg' src = 'captcha.php' style = 'width:100px; height:20px;'></img>
	<button type = 'button' onclick = "refresh()">Refresh</button><br><br>
	<button type = 'button' onclick = 'submit()'>Login</button>
	<form id = 'passForm' action = 'admin.php' method = 'post'>
		<input id = 'passInput' type = 'hidden' name = 'pass' value = ''></input>
	</form>
</center>


</body>
</html>