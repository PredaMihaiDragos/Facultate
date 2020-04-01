<?php

session_start();
$mail = $_GET['mail'];
$key = $_GET['key'];

?>

<!DOCTYPE html>
<html>
<body>

<div style = "position: relative; top:30px; left:50px;">

Username: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  <input type = 'text' id = 'regUser'></input><br><br>
Password: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <input oninput = 'checkPass(this.value)' type = 'password' id = 'regPass'></input><br><br>
Password again: <input type = 'password' id = 'regPass2'></input><br><br>

	<canvas id="power1" style = "position: relative; top:-100px; left:260px;">
	Your browser does not support the HTML5 canvas tag.
	</canvas>
	
	<canvas id="power2" style = "position: relative; top:-100px; left:-28px;">
	Your browser does not support the HTML5 canvas tag.
	</canvas>
	
	<canvas id="power3" style = "position: relative; top:-100px; left:-315px;">
	Your browser does not support the HTML5 canvas tag.
	</canvas>
	
	<canvas id="power4" style = "position: relative; top:-254px; left:310px;">
	Your browser does not support the HTML5 canvas tag.
	</canvas>
	<button type = 'button' onclick = "Validate()" style = "position: relative; top:-290px; left:-200px;">Register</button>
</div>

<script>

var c=document.getElementById("power1");
var ctx=c.getContext("2d");
ctx.rect(20,20,10,10);
ctx.stroke();

var c=document.getElementById("power2");
var ctx=c.getContext("2d");
ctx.rect(20,20,10,10);
ctx.stroke();

var c=document.getElementById("power3");
var ctx=c.getContext("2d");
ctx.rect(20,20,10,10);
ctx.stroke();

var c=document.getElementById("power4");
var ctx=c.getContext("2d");
ctx.rect(20,20,10,10);
ctx.stroke();

function scorePassword(pass) 
{
    var score = 0;
    if (!pass) return score;

    var letters = new Object();
    for (var i=0; i<pass.length; i++) {
        letters[pass[i]] = (letters[pass[i]] || 0) + 1;
        score += 5.0 / letters[pass[i]];
    }

    var variations = {
        digits: /\d/.test(pass),
        lower: /[a-z]/.test(pass),
        upper: /[A-Z]/.test(pass),
        nonWords: /\W/.test(pass),
    }

    variationCount = 0;
    for (var check in variations) {
        variationCount += (variations[check] == true) ? 1 : 0;
    }
    score += (variationCount - 1) * 10;

    return parseInt(score);
}

function checkPass(pass)
{
	var s = scorePassword(pass);
	if(s < 20)
	{
		var c=document.getElementById("power1");
		var ctx=c.getContext("2d");
		ctx.fillStyle= "red";
		ctx.fill();
		
		var c=document.getElementById("power2");
		var ctx=c.getContext("2d");
		ctx.fillStyle= "red";
		ctx.fill();
		
		var c=document.getElementById("power3");
		var ctx=c.getContext("2d");
		ctx.fillStyle= "red";
		ctx.fill();
		
		var c=document.getElementById("power4");
		var ctx=c.getContext("2d");
		ctx.fillStyle= "red";
		ctx.fill();
	}
	else if(s < 40)
	{
		var c=document.getElementById("power1");
		var ctx=c.getContext("2d");
		ctx.fillStyle= "green";
		ctx.fill();
		
		var c=document.getElementById("power2");
		var ctx=c.getContext("2d");
		ctx.fillStyle= "red";
		ctx.fill();
		
		var c=document.getElementById("power3");
		var ctx=c.getContext("2d");
		ctx.fillStyle= "red";
		ctx.fill();
		
		var c=document.getElementById("power4");
		var ctx=c.getContext("2d");
		ctx.fillStyle= "red";
		ctx.fill();
	}
	else if(s < 60)
	{
		var c=document.getElementById("power1");
		var ctx=c.getContext("2d");
		ctx.fillStyle= "green";
		ctx.fill();
		
		var c=document.getElementById("power2");
		var ctx=c.getContext("2d");
		ctx.fillStyle= "green";
		ctx.fill();
		
		var c=document.getElementById("power3");
		var ctx=c.getContext("2d");
		ctx.fillStyle= "red";
		ctx.fill();
		
		var c=document.getElementById("power4");
		var ctx=c.getContext("2d");
		ctx.fillStyle= "red";
		ctx.fill();
	}
	else if(s < 80)
	{
		var c=document.getElementById("power1");
		var ctx=c.getContext("2d");
		ctx.fillStyle= "green";
		ctx.fill();
		
		var c=document.getElementById("power2");
		var ctx=c.getContext("2d");
		ctx.fillStyle= "green";
		ctx.fill();
		
		var c=document.getElementById("power3");
		var ctx=c.getContext("2d");
		ctx.fillStyle= "green";
		ctx.fill();
		
		var c=document.getElementById("power4");
		var ctx=c.getContext("2d");
		ctx.fillStyle= "red";
		ctx.fill();
	}
	else if(s > 80)
	{
		var c=document.getElementById("power1");
		var ctx=c.getContext("2d");
		ctx.fillStyle= "green";
		ctx.fill();
		
		var c=document.getElementById("power2");
		var ctx=c.getContext("2d");
		ctx.fillStyle= "green";
		ctx.fill();
		
		var c=document.getElementById("power3");
		var ctx=c.getContext("2d");
		ctx.fillStyle= "green";
		ctx.fill();
		
		var c=document.getElementById("power4");
		var ctx=c.getContext("2d");
		ctx.fillStyle= "green";
		ctx.fill();
	}

}

function Validate()
{
	var user = document.getElementById('regUser').value;
	var pass = document.getElementById('regPass').value;
	var pass2 = document.getElementById('regPass2').value;
	if(scorePassword(pass) < 20) alert('Parola este prea usor de ghicit.');
	else
	{
		if(pass != pass2)
		{
			alert('Cele doua parole nu corespund.');
			document.getElementById('regPass2').focus();
			document.getElementById('regPass2').value = "";
		}
		else
		{
			var response = "";
			var xmlhttp=new XMLHttpRequest();
			xmlhttp.open("GET","register2.php?mail=<?=$_GET['mail']?>&key=<?=$_GET['key']?>&pass=" + pass + "&user=" + user,false);
			xmlhttp.send();
			if (xmlhttp.readyState==4 && xmlhttp.status==200) response=xmlhttp.responseText;
			alert(response);
		}
	}

}
</script>


</body>
</html>