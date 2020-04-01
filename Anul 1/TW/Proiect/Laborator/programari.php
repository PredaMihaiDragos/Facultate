<?php session_start(); ?>
<html>

<head>

<script type = 'text/javascript'>

function letterCheck(x)
{
	var v = x.value;
	var matches = v.match(/\d+/g);
	if(matches != null) 
	{
		for(var y = 1; y < matches; y++)
		{
			x.value = v.replace(/\d+/g, '');
		}
		alert('Acest camp nu poate fi format din cifre.');
	}
}

function cnpCheck(x)
{
	if(!ccnp(x.value)) 
	{
		x.value = "";
		alert('CNP invalid.');
		x.focus();
	}
}


function map(fn, arr){
	var ret = [];
	for(var x = 0; x < arr.length; x++)
		ret.push(fn(arr[x]));
	return ret;
}

function reduce(fn, arr, initial){
	function iter(idx, ret){
		if(idx >= arr.length)
			return ret;
		else
			return iter(idx+1, fn(arr[idx], ret));
 	}
	return iter(initial ? 0 : 1, initial || arr[0]);
}

function sum(arr) { return reduce(function(x, y){ return x + y;}, arr, 0); }

function ccnp(cnp){
	if(cnp.length != 13)
		return false;

	cnp = map(parseInt, cnp.split(''));

	var coefs = [2, 7, 9, 1, 4, 6, 3, 5, 8, 2, 7, 9];
	var idx = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11];

	var s = map(function(x){return coefs[x] * cnp[x];}, idx);
	s = sum(s) % 11;

	return (s < 10 && s == cnp[12]) || (s == 10 && cnp[12] == 1);
}

function daClick()
{
	document.getElementById('exTrim').innerHTML = "Pe baza biletului de trimitere, analizele aflate in contract cu C.A.S sunt gratuite. Alte analize se pot efectua contra-cost.<br>Programarile pentru analizele cu trimitere se fac de luni pana vineri de la ora 08:00 la ora 15:00.";

}

function nuClick()
{
	document.getElementById('exTrim').innerHTML = "Fara trimitere, toata gama de analize se poate efectua contra-cost.<br>Programarile pentru analizele fara trimitere se pot face in orice zi a saptamanii intre orele 08:00 si 20:00."

}

function submit()
{
	if(document.getElementById('nume').value.length < 3 || document.getElementById('prenume').value.length < 3 || 
	document.getElementById('cnp').value.length < 13 || (document.getElementById('trimitere').checked == false && 
	document.getElementById('faraTrimitere').checked == false) || document.getElementById('phone').value.length < 10 ||
	document.getElementById('mail').value.search('@') == -1 || document.getElementById('mail').value.search('.') == -1)
	{
		if(document.getElementById('nume').value.length < 3) document.getElementById('nume').style.backgroundColor = '#FF3366'
		if(document.getElementById('prenume').value.length < 3) document.getElementById('prenume').style.backgroundColor = '#FF3366'
		if(document.getElementById('cnp').value.length < 13) document.getElementById('cnp').style.backgroundColor = '#FF3366'
		if(document.getElementById('trimitere').checked == false && document.getElementById('faraTrimitere').checked == false) document.getElementById('exTrim').innerHTML = "<font color = 'blue'>Alege o varianta!</font>";
		if(document.getElementById('phone').value.length < 10) document.getElementById('phone').style.backgroundColor = '#FF3366'
		if(document.getElementById('mail').value.search('@') == -1 || document.getElementById('mail').value.search('.') == -1) document.getElementById('mail').style.backgroundColor = '#FF3366'
		alert('Completeaza toate cerintele obligatorii cu valori corecte!');
	}
	else
	{
		var nume = document.getElementById('nume').value;
		var prenume = document.getElementById('prenume').value;
		var cnp = parseInt(document.getElementById('cnp').value);
		var trim = 0;
			if(document.getElementById('trimitere').checked) trim = 1;
		var mail = document.getElementById('mail').value;
		var phone = document.getElementById('phone').value;
		var liber = document.getElementById('liber').value;
		var alte = document.getElementById('alte').value;
		
		var xmlhttp;
		if(window.XMLHttpRequest) xmlhttp=new XMLHttpRequest();
		else xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
		
		<?php $_SESSION['key'] = rand(1, 99999999999); ?>
		
		xmlhttp.onreadystatechange=function()
		{
			if (xmlhttp.readyState==4 && xmlhttp.status==200)
			{
				if(xmlhttp.responseText == 'wrongCode')
				{
					alert('A aparut o problema. Incearca din nou.');
				}
				else 
				{
					document.write("<center> <img id = 'title' src = './images/programariTitle.png'> </img> </center><br><br> <font color = 'blue' size = 5>Ai facut cu succes programarea. Daca iti va fi acceptata, vei fi contactat prin mail sau prin telefon.<br> Codul programarii tale este: <font color = 'red' size = 5><b>" + <?=$_SESSION['key']?> + "</b></font>");
				}
			}
		}
		
		xmlhttp.open("POST","programare.php",true);
		xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
		xmlhttp.send("nume=" + nume + "&prenume=" + prenume + "&cnp=" + cnp + "&trim=" + trim + "&mail=" + mail + "&phone=" + phone + "&liber=" + liber + "&alte=" + alte + "&key=" + <?=$_SESSION['key']?>);
		
	}
}
</script>

<style>

	textarea
	{
		resize: none;
	}

</style>

</head>

<body>


<center> <img id = 'title' src = './images/programariTitle.png'> </img> </center>
<br><br>
<font size = 4>Acum iti oferim oportunitatea sa te programezi online! Completeaza urmatorul formular.</font>
<br><br>
<b>Cerinte obligatorii:</b>
<br><br>

&nbsp;&nbsp;Nume: &nbsp;&nbsp;<input type = 'text' id = 'nume' onkeyup = 'letterCheck(this)' onfocus = 'this.style.backgroundColor = "white";' maxlength = 20></input><br><br>
Prenume: <input type = 'text' id = 'prenume' onkeyup = 'letterCheck(this)' onfocus = 'this.style.backgroundColor = "white";' maxlength = 40'></input> <font size = 2>( in cazul in care aveti mai multe prenume, specificati-le pe toate despartite de " " (spatiu). )</font><br><br>
&nbsp;&nbsp;&nbsp;C.N.P:&nbsp;  <input type = 'text' id = 'cnp' maxlength = 13 onchange = 'cnpCheck(this)' onfocus = 'this.style.backgroundColor = "white";'></input><br><font size = 2>(cod numeric personal)</font><br>
<br>
Numar de telefon:&nbsp;  <input type = 'text' id = 'phone' maxlength = 10 onfocus = 'this.style.backgroundColor = "white";'></input><br>
<br>
Mail: <input type = 'text' id = 'mail' maxlength = 35 onfocus = 'this.style.backgroundColor = "white";'></input><br><br>
Ai trimitere? 
<br>
<form>
Da<input type = 'radio' name = 'trimitereInput' onchange = 'daClick()' id = 'trimitere'>
Nu<input type = 'radio' name = 'trimitereInput' onchange = 'nuClick()' id = 'faraTrimitere'>
</form>

<div id = 'exTrim' style = 'border: 2px solid; width:800px; height:60px;'></div>

<br><br>
<b>Cerinte suplimentare</b> (optional):

<br><br>
Cand esti liber pentru a veni:<br>
<textarea id = 'liber' maxlength = 170 style = "width:300px; height:100px;">
</textarea>

<div id = 'divAlte' style = 'position: absolute; top:653px; left:400px;'>
Alte detalii: (poti include aici si intrebari)<br>
<textarea id = 'alte' maxlength = 170 style = "width:300px; height:100px;">
</textarea>

</div>

<br><br>
<button type = 'button' onclick = 'submit()'>Programeaza-te!</button>

</body>
</html>