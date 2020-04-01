<html>

<head>

<?php

$file = fopen("ChestionarBase.txt", "r");
$db = fread($file, filesize("ChestionarBase.txt")) or die("Error");
fclose($file);

$r1 = explode(" ", $db, 5);
$r2 = explode(" ", $r1[4], 5);
$r3 = explode(" ", $r2[4], 5);
$r4 = explode(" ", $r3[4], 5);
$r5 = explode(" ", $r4[4], 5);

$r1[0] = intval($r1[0]);
$r1[1] = intval($r1[1]);
$r1[2] = intval($r1[2]);
$r1[3] = intval($r1[3]);

$r2[0] = intval($r2[0]);
$r2[1] = intval($r2[1]);
$r2[2] = intval($r2[2]);
$r2[3] = intval($r2[3]);

$r3[0] = intval($r3[0]);
$r3[1] = intval($r3[1]);
$r3[2] = intval($r3[2]);
$r3[3] = intval($r3[3]);

$r4[0] = intval($r4[0]);
$r4[1] = intval($r4[1]);
$r4[2] = intval($r4[2]);
$r4[3] = intval($r4[3]);

$r5[0] = intval($r5[0]);
$r5[1] = intval($r5[1]);
$r5[2] = intval($r5[2]);
$r5[3] = intval($r5[3]);

$sr1 = $r1[0] + $r1[1] + $r1[2] + $r1[3];
$sr2 = $r2[0] + $r2[1] + $r2[2] + $r3[3];
$sr3 = $r3[0] + $r3[1] + $r3[2] + $r3[3];
$sr4 = $r4[0] + $r4[1] + $r4[2] + $r4[3];
$sr5 = $r5[0] + $r5[1] + $r5[2] + $r5[3];

$pr1 = array(round($r1[0] * 100 / $sr1, 2), round($r1[1] * 100 / $sr1, 2), round($r1[2] * 100 / $sr1, 2), round($r1[3] * 100 / $sr1, 2));
$pr2 = array(round($r2[0] * 100 / $sr2, 2), round($r2[1] * 100 / $sr2, 2), round($r2[2] * 100 / $sr2, 2), round($r2[3] * 100 / $sr2, 2));
$pr3 = array(round($r3[0] * 100 / $sr3, 2), round($r3[1] * 100 / $sr3, 2), round($r3[2] * 100 / $sr3, 2), round($r3[3] * 100 / $sr3, 2));
$pr4 = array(round($r4[0] * 100 / $sr4, 2), round($r4[1] * 100 / $sr4, 2), round($r4[2] * 100 / $sr4, 2), round($r4[3] * 100 / $sr4, 2));
$pr5 = array(round($r5[0] * 100 / $sr5, 2), round($r5[1] * 100 / $sr5, 2), round($r5[2] * 100 / $sr5, 2), round($r5[3] * 100 / $sr5, 2));


function drawLoadingBar($percent)
{
	
}

?>

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

function getRadioValue(name)
{
	var elem = document.getElementsByName(name);
	for(var i = 0; i < elem.length; i++)
	{
		if(elem[i].checked == true) return elem[i].value;
	}
}

function submit()
{
	if(document.getElementById('nume').value.length < 3 || document.getElementById('prenume').value.length < 3)
	{
		if(document.getElementById('nume').value.length < 3) document.getElementById('nume').style.backgroundColor = '#FF3366'
		if(document.getElementById('prenume').value.length < 3) document.getElementById('prenume').style.backgroundColor = '#FF3366'
		alert('Completeaza toate cerintele obligatorii cu valori corecte!');
	}
	else
	{
		var nume = document.getElementById('nume').value;
		var prenume = document.getElementById('prenume').value;
		var r1 = getRadioValue("1");
		var r2 = getRadioValue("2");
		var r3 = getRadioValue("3");
		var r4 = getRadioValue("4");
		var r5 = getRadioValue("5");
		
		var xmlhttp;
		if(window.XMLHttpRequest) xmlhttp=new XMLHttpRequest();
		else xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
		
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
					alert("Trimis!");
				}
			}
		}
		
		xmlhttp.open("POST","chestionarSubmit.php",true);
		xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
		xmlhttp.send("nume=" + nume + "&prenume=" + prenume + "&r1=" + r1 + "&r2=" + r2 + "&r3=" + r3 + "&r4=" + r4 + "&r5=" + r5);
		
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


<center> <img id = 'title' src = './images/chestionarTitle.png'> </img> </center>
<br><br>
<font size = 4>Completeaza urmatorul formular pentru a ne ajuta sa ne imbunatatim serviciile.</font>
<br><br>

&nbsp;&nbsp;Nume: &nbsp;&nbsp;<input type = 'text' id = 'nume' onkeyup = 'letterCheck(this)' onfocus = 'this.style.backgroundColor = "white";' maxlength = 20></input><br><br>
Prenume: <input type = 'text' id = 'prenume' onkeyup = 'letterCheck(this)' onfocus = 'this.style.backgroundColor = "white";' maxlength = 40'></input> <font size = 2>( in cazul in care aveti mai multe prenume, specificati-le pe toate despartite de " " (spatiu). )</font><br><br>
<br>
1. Competenta profesionala:&nbsp;  <br>
 <input type="radio" name="1" value="fb" checked> Foarte buna&nbsp; (<?php echo $pr1[0];?>%)<br>
  <input type="radio" name="1" value="b"> Buna&nbsp; (<?php echo $pr1[1];?>%)<br>
  <input type="radio" name="1" value="s"> Satisfacatoare&nbsp; (<?php echo $pr1[2];?>%)<br>
  <input type="radio" name="1" value="n"> Nesatisfacatoare&nbsp; (<?php echo $pr1[3];?>%)<br><br>
<br>

2. Promptitudinea in rezolvarea solicitarilor:&nbsp;  <br>
 <input type="radio" name="2" value="fb" checked> Foarte buna&nbsp; (<?php echo $pr2[0];?>%)<br>
  <input type="radio" name="2" value="b"> Buna&nbsp; (<?php echo $pr2[1];?>%)<br>
  <input type="radio" name="2" value="s"> Satisfacatoare&nbsp; (<?php echo $pr2[2];?>%)<br>
  <input type="radio" name="2" value="n"> Nesatisfacatoare&nbsp; (<?php echo $pr2[3];?>%)<br><br>
<br>

3. Calitatea serviciilor:&nbsp;  <br>
 <input type="radio" name="3" value="fb" checked> Foarte buna&nbsp; (<?php echo $pr3[0];?>%)<br>
  <input type="radio" name="3" value="b"> Buna&nbsp; (<?php echo $pr3[1];?>%)<br>
  <input type="radio" name="3" value="s"> Satisfacatoare&nbsp; (<?php echo $pr3[2];?>%)<br>
  <input type="radio" name="3" value="n"> Nesatisfacatoare&nbsp; (<?php echo $pr3[3];?>%)<br><br>
<br>

4. Pretul perceput pentru servicii:&nbsp;  <br>
 <input type="radio" name="4" value="fb" checked> Foarte buna&nbsp; (<?php echo $pr4[0];?>%)<br>
  <input type="radio" name="4" value="b"> Buna&nbsp; (<?php echo $pr4[1];?>%)<br>
  <input type="radio" name="4" value="s"> Satisfacatoare&nbsp; (<?php echo $pr4[2];?>%)<br>
  <input type="radio" name="4" value="n"> Nesatisfacatoare&nbsp; (<?php echo $pr4[3];?>%)<br><br>
<br>

5. Disponibilitatea de comunicare a personalului:&nbsp;  <br>
 <input type="radio" name="5" value="fb" checked> Foarte buna&nbsp; (<?php echo $pr5[0];?>%)<br>
  <input type="radio" name="5" value="b"> Buna&nbsp; (<?php echo $pr5[1];?>%)<br>
  <input type="radio" name="5" value="s"> Satisfacatoare&nbsp; (<?php echo $pr5[2];?>%)<br>
  <input type="radio" name="5" value="n"> Nesatisfacatoare&nbsp; (<?php echo $pr5[3];?>%)<br><br>
<br>
</div>

<button type = 'button' onclick = 'submit()'>Trimite!</button>

</body>
</html>