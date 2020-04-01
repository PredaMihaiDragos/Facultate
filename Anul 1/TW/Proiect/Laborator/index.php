<?php session_start(); ?>
<!DOCTYPE html>
<html>

<head>
<!--
<script src="//code.jquery.com/jquery-1.10.2.js"></script>
<script src="//code.jquery.com/ui/1.10.4/jquery-ui.js"></script> -->

	<style>
		button.buttons
		{
			display:inline;
			color: black;
			font-size:26px;
			border: 0; 
			background: transparent;
			text-decoration:none;
			outline: none;
		}
	</style>
	
<script type='text/javascript'>
var current = 0;
function over(x)
{
	if(x != current) x.style.color = 'blue';
}

function out(x)
{
	if(x != current) x.style.color = 'black';
}

function indexClick(x)
{
	document.getElementById("content").src = 'home.php';
	if(current != x)
	{
		try { current.style.color = 'black'; }
		catch(err) {}
		current = x;
	}
	window.location.hash = '#homeMenu';
}

function orarClick(x)
{
	document.getElementById("content").src = 'orar.php';
	if(current != x)
	{
		try { current.style.color = 'black'; }
		catch(err) {}
		current = x;
	}
	window.location.hash = '#orarMenu';
}

function analizeClick(x)
{
	document.getElementById("content").src = 'analize.php';
	if(current != x)
	{
		try { current.style.color = 'black'; }
		catch(err) {}
		current = x;
	}
}

function programariClick(x)
{
	document.getElementById("content").src = 'programari.php';
	if(current != x)
	{
		try { current.style.color = 'black'; }
		catch(err) {}
		current = x;
	}
	window.location.hash = '#programariMenu';
}

function programariClickOrar()
{
	document.getElementById("content").src = 'programari.php';
	try { current.style.color = 'black'; }
	catch(err) {}
	current = document.getElementById('programari');
	current.style.color = 'blue';
	window.location.hash = '#programariMenu';
}

function rezultateClick(x)
{
	document.getElementById("content").src = 'rezultate.php';
	if(current != x)
	{
		try { current.style.color = 'black'; }
		catch(err) {}
		current = x;
	}
	window.location.hash = '#rezultateMenu';
}

function certificariClick(x)
{
	document.getElementById("content").src = 'certificari.php';
	if(current != x)
	{
		try { current.style.color = 'black'; }
		catch(err) {}
		current = x;
	}
	window.location.hash = '#certificariMenu';
}

function chestionarClick(x)
{
	document.getElementById("content").src = 'chestionar.php';
	if(current != x)
	{
		try { current.style.color = 'black'; }
		catch(err) {}
		current = x;
	}
	window.location.hash = '#chestionarMenu';
}

function contactClick(x)
{
	document.getElementById("content").src = 'contact.php';
	if(current != x)
	{
		try { current.style.color = 'black'; }
		catch(err) {}
		current = x;
	}
	window.location.hash = '#contactMenu';
}

function loginClick()
{
	document.getElementById('logDiv').style.visibility = "visible";
	blurPage();
}

function exitLogin()
{
	document.getElementById('logDiv').style.visibility = "hidden";
	document.getElementById('logDiv').style.top = "200px";
	document.getElementById('logDiv').style.left = "600px";
	unBlurPage();
}

function blurPage()
{
	document.getElementById('blurPage').style.visibility = "visible";
}

function unBlurPage()
{
	document.getElementById('blurPage').style.visibility = "hidden";
}

function forgotClick()
{
	document.getElementById('forgotDiv').style.visibility = "visible";
	document.getElementById('forgotDiv').style.top = document.getElementById('logDiv').style.top;
	document.getElementById('forgotDiv').style.left = document.getElementById('logDiv').style.left;
	
	document.getElementById('logDiv').style.visibility = "hidden";
	document.getElementById('logDiv').style.top = "200px";
	document.getElementById('logDiv').style.left = "600px";
	blurPage();
}

function exitForgot()
{
	document.getElementById('forgotDiv').style.visibility = "hidden";
	document.getElementById('forgotDiv').style.top = "200px";
	document.getElementById('forgotDiv').style.left = "600px";
	unBlurPage();
}

function exitReg()
{
	document.getElementById('regSucces').style.visibility = "hidden";
	document.getElementById('regSucces').style.top = "200px";
	document.getElementById('regSucces').style.left = "600px";
	unBlurPage();
}

/*function Register()
{
	<?php $_SESSION['regkey'] = rand(1, 99999999999); ?>
	
	var mail = document.getElementById('regInput').value;
	if(mail.search("@") != -1 && mail.search(".") != -1 && mail.length > 5)
	{
		var response = "";
		
		var xmlhttp=new XMLHttpRequest();
		xmlhttp.open("GET","register.php?mail=" + mail + "&key=<?=$_SESSION['regkey']?>",false);
		xmlhttp.send();
		if (xmlhttp.readyState==4 && xmlhttp.status==200) response=xmlhttp.responseText;
		if(response == 'succes')
		{
			document.getElementById('regSucces').style.visibility = "visible";
			blurPage();
		}
		else if(response == 'KeyError')
		{
			alert("Anti-spam: Nu poti face mai multe conturi in acelasi timp. Daca ai gresit mailul, dai un refresh la pagina.");
		}
		else if(response == 'exist')
		{
			alert('Exista deja un cont cu acest mail. Daca vrei sa te loghezi, click pe butonul "Login".');
		}
		else if(response == 'time')
		{
			alert('Anti-spam: Poti inregistra maxim un cont pe zi pe aceeasi adresa de mail. In caz ca nu ai primit mailul, contacteaza administratorul.');
		}
		else alert("A aparut o eroare. Reincearca. Daca problema persista, contacteaza administratorul.");
			
	}
	else alert("Mail introdus gresit.\nExemplu: adina.preda@gmail.com");
}*/


</script>

<script>
  /*$(function() {
    $( "#logDiv" ).draggable();
  });
  $(function() {
    $( "#forgotDiv" ).draggable();
  });
  $(function() {
    $( "#regSucces" ).draggable();
  });*/
 </script>
  
</head>

<body onload = 'bodyLoad()' onkeydown='escKey(event)' style = "margin-left: auto; margin-right: auto; background: url(./images/indexBack.png) no-repeat center center fixed; background-size: 100% 100%">


<img id = 'header' src = './images/indexHead.png' style = "position: absolute; left: 0px; top: -15px; width:100%; height:170px;"></img>

<div name = "container" style="position: absolute; top:100px; width:100%;">

	
	<div style = "position: relative; top:50px; width:1200px; height:35px; margin: auto; background: url('./images/buttonsBack.png');">
		<!-- <button type = "button" onclick = "loginClick()" style = "position: absolute; top:-30px;">Login</button>
		
		<input id = "regInput" type = "text" placeholder = "Enter your mail" maxlength = "40"  style = "position: absolute; top:-30px; left:730px;"></input>
		<button type = "button" onclick = "Register()" style = "position: absolute; top:-30px; left:900px;">Register</button> -->
		
		<button type = "button" id = 'home' class = 'buttons' onclick = 'indexClick(this)' onmouseover='over(this)' onmouseout='out(this)'>Home</button> &nbsp;&nbsp; <font color = 'red' size = 5><b> | </b></font> &nbsp;&nbsp;
		<button type = "button" id = 'orar' class = 'buttons' onclick = 'orarClick(this)' onmouseover='over(this)' onmouseout='out(this)'>Orar</button> &nbsp;&nbsp; <font color = 'red' size = 5><b> | </b></font> &nbsp;&nbsp;
		<button type = "button" id = 'programari' class = 'buttons' onclick = 'programariClick(this)' onmouseover='over(this)' onmouseout='out(this)'>Programari</button> &nbsp;&nbsp; <font color = 'red' size = 5><b> | </b></font> &nbsp;&nbsp;
		<button type = "button" id = 'despre' class = 'buttons' onclick = 'analizeClick(this)' onmouseover='over(this)' onmouseout='out(this)'>Analize</button> &nbsp;&nbsp; <font color = 'red' size = 5><b> | </b></font> &nbsp;&nbsp;
		<button type = "button" id = 'rezultate' class = 'buttons' onclick = 'rezultateClick(this)' onmouseover='over(this)' onmouseout='out(this)'>Rezultate</button> &nbsp;&nbsp; <font color = 'red' size = 5><b> | </b></font> &nbsp;&nbsp;
		<button type = "button" id = 'certificari' class = 'buttons' onclick = 'certificariClick(this)' onmouseover='over(this)' onmouseout='out(this)'>Acreditari</button> &nbsp;&nbsp; <font color = 'red' size = 5><b> | </b></font> &nbsp;&nbsp;
		<button type = "button" id = 'chestionar' class = 'buttons' onclick = 'chestionarClick(this)' onmouseover='over(this)' onmouseout='out(this)'>Chestionar</button> &nbsp;&nbsp; <font color = 'red' size = 5><b> | </b></font> &nbsp;&nbsp;
		<button type = "button" id = 'contact' class = 'buttons' onclick = 'contactClick(this)' onmouseover='over(this)' onmouseout='out(this)'>Contact</button>
		<br><br>
		<iframe style = "position: relative; left:140px; height:750px; width:870px;" id = 'content' src="nothing.php" scrolling="auto"></iframe>
		<img id = 'phone' src = './images/phone.png' style = "position: absolute; left: 300px; top: -90px; height:100px; width:400px;"></img>
		<font face = 'Gabriola' color = "blue" size = 8 style = "position: relative; top: -994px;"><b>laborator laborator Laborator analize medicale</b></font>
		<img src = './images/heart.png' style = "position: relative; top: -980px; left:30px; width:60px; height:60px;"></img>
		<font face = 'Gabriola' color = "blue" size = 8 style = "position: relative; left:70px; top: -991px;"><b>Preda Cati Adina</b></font>
	</div>
	
	<!-- <div id = "logDiv" style = "position: fixed; top:200px; left:600px; width:0px; height:0px; z-index:5000; visibility:hidden;">
		<img src = "./images/LogBack.png"></img>
		<span style = "position: relative; top:-270px; left:10px;">
			<font color = 'white'>
				Username: <input type = "text" id = "logUser"></input><br><br>
				Password: <input type = "text" id = "logUser"></input><br><br>
			</font>
			<button type = "button" onclick = "Login()">Login</button><br>
			<button type = "button" onclick = "forgotClick()" style = "border: 0; background: transparent; outline: none;"><font color = 'white'>Forgot&nbsp;password</font></button>
		</span>
		<img onclick = "exitLogin()" src = "./images/x.png" style = "position: relative; top:-450px; left:380px;"></img>
	</div>
	
	<div id = "forgotDiv" style = "position: fixed; top:200px; left:600px; width:0px; height:0px; z-index:5000; visibility:hidden;">
		<img src = "./images/LogBack.png"></img>
		
		<span style = "position: relative; top:-270px; left:10px;">
			<font color = 'white'>
				Mail&nbsp;/&nbsp;Username: <input type = "text" id = "forgotInput"></input><br><br>
			</font>
			<button type = "button" onclick = "ForgotPass()">Forgot&nbsp;Password</button><br><br>
			<font color = 'white'> 
				Mail&nbsp;example:&nbsp;adina.preda@gmail.com<br>
				Username&nbsp;example:&nbsp;Adina
			</font>
		</span>
		<img onclick = "exitForgot()" src = "./images/x.png" style = "position: relative; top:-425px; left:380px;"></img>
		
	</div>
	
	
	<div id = "regSucces" style = "position: fixed; top:200px; left:600px; width:0px; height:0px; z-index:5000; visibility:hidden;">
		<img src = "./images/LogBack.png"></img>
		<span style = "position: relative; top:-230px; left:10px; ">
			<font color = 'white'> 
			Contul&nbsp;a&nbsp;fost&nbsp;inregistrat&nbsp;cu&nbsp;succes. 
			Pentru&nbsp;a&nbsp;avea&nbsp;acces&nbsp;la&nbsp;contul&nbsp;tau,&nbsp;intra&nbsp;pe&nbsp;mail,&nbsp;si&nbsp;urmareste instructiunile&nbsp;din&nbsp;mailul&nbsp;primit&nbsp;de&nbsp;la&nbsp;noi.
			</font>
		</span>
		<img onclick = "exitReg()" src = "./images/x.png" style = "position: relative; top:-340px; left:380px;"></img>
	</div> -->
	
</div>

<div id = "blurPage" style = "position: fixed; top:-10px; width:100%; height:110%; z-index:4000; background-color:black; opacity:0.6; visibility:hidden;"></div>
		<div id = 'footer' style = 'position: absolute; top:1000px; width:100%'><center><font size = 1>Copyright &copy; <?php echo date('Y');?> Preda Mihai | Toate drepturile rezervate</font></center></div>
<script type = 'text/javascript'> 

<?php 
/*
if(!empty($_GET['action']))
{
	$action = $_GET['action'];
	$mail = $_GET['mail'];
	$key = $_GET['key'];
	if($action == 'validate')
	{
		echo "var current = 'validate';";
		echo "document.getElementById('content').src = 'validate.php?mail=$mail&key=$key';";
	}
	else 
	{
		echo "var current = document.getElementById('home');";
		echo "document.getElementById('home').style.color = 'blue';"; 
	}
}
else 
{
	echo "var current = document.getElementById('home');";
	echo "document.getElementById('home').style.color = 'blue';"; 
}
*/
?>

function escKey(e)
{
	if(e.keyCode == 27)
	{
		if(document.getElementById('logDiv').style.visibility == "visible") exitLogin();
		else if(document.getElementById('forgotDiv').style.visibility == "visible") exitForgot();
		else if(document.getElementById('regSucces').style.visibility == "visible") exitReg();
	}
}

var oldLeft = window.pageXOffset;

window.onscroll = function (e) 
{
	if(window.pageXOffset != oldLeft)
	{
		var x = parseInt(document.getElementById('header').style.left);
		document.getElementById('header').style.left = x + (window.pageXOffset - oldLeft) + 'px';
		oldLeft = window.pageXOffset;
		
	}
}
var clickNumber = 0;
window.onclick = function(e)
{
	unShowImage();
	clickNumber++;
}

function bodyLoad()
{
	if(window.location.hash)
	{
		var hash = window.location.hash.substring(1);
		if(hash == 'orarMenu')
		{
			var current = document.getElementById('orar');
			current.style.color = 'blue';
			orarClick(current);
		}
		else if(hash == 'programariMenu')
		{
			var current = document.getElementById('programari');
			current.style.color = 'blue';
			programariClick(current);
		}
		else if(hash == 'rezultateMenu')
		{
			var current = document.getElementById('rezultate');
			current.style.color = 'blue';
			rezultateClick(current);
		}
		else if(hash == 'certificariMenu')
		{
			var current = document.getElementById('certificari');
			current.style.color = 'blue';
			certificariClick(current);
		}
		else if(hash == 'chestionarMenu')
		{
			var current = document.getElementById('chestionar');
			current.style.color = 'blue';
			chestionarClick(current);
		}
		else if(hash == 'contactMenu') 
		{
			var current = document.getElementById('contact');
			current.style.color = 'blue';
			contactClick(current);
		}
		else if(hash == 'admin') 
		{
			var current = -1;
			<?php
			error_reporting(0);
				if($_POST['pass']) echo "document.getElementById('content').src = 'adminver.php?pass=' + '" . $_POST['pass'] . "';";
				else echo "document.getElementById('content').src = 'adminver.php';";
			?>
			document.getElementById("content").style.width="1000px";
		}
		else
		{
			var current = document.getElementById('home');
			current.style.color = 'blue';
			indexClick(current);
		}
	}
	else
	{
		var current = document.getElementById('home');
		current.style.color = 'blue';
		indexClick(current);
	}
}

var click;
function showImage(url)
{
	var img = document.getElementById('showImages');
	img.style.visibility = "visible";
	img.src = url;
	click = clickNumber;
}

function unShowImage()
{
	if(clickNumber != click)
	{
		var img = document.getElementById('showImages');
		img.style.visibility = "hidden";
	}
}

</script>
<img src = '' id = 'showImages' border = '5' style = 'position:fixed; top:50%; left:50%; margin-top:-300px; margin-left:-250px; height:600px; width:500px; visibility:hidden;'></img>
</body>
</html>