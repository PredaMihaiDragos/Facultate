<html>
<body>



<center> <img id = 'title' src = './images/rezultateTitle.png'> </img> </center>
<br><br>
<center>

<?php

if(!empty($_GET['CNP']) && !empty($_GET['ID'])):
	$cnp = $_GET['CNP'];
	$tempid = $_GET['ID'];
	
	$id = explode("-", $tempid);

	$handle = fopen('database/' . $id[0] . '.' . $id[1] . '.' . $cnp . ".txt", "r");
	if ($handle) 
	{
		$i1 = 0;
		$i2 = 0;
		$i3 = 0;
		$i4 = 0;
		$i5 = 0;
		while (($line = fgets($handle)) !== false) 
		{
			$x = explode("=", $line, 2);
			if($x[0] === "np") 			$name = $x[1];
			else if($x[0] === "cuv") 	$cuv = $x[1];
			else if($x[0] === "codv")	$codv = $x[1];
			else if($x[0] === "idp") 	$idp = $x[1];
			else if($x[0] === "db") 	$db = $x[1];
			else if($x[0] === "rec") 	$rec = $x[1];
			else if($x[0] === "trm") 	$trm = $x[1];
			else if($x[0] === "orap") 	$orap = $x[1];
			else if($x[0] === "orar") 	$orar = $x[1];
			else if($x[0] === "pard") 	$pard = $x[1];
			else if($x[0] === "doctor") $doctor = $x[1];
			else if($x[0] === "aDen" . $i1)
			{
				$aDen[$i1] = $x[1];
				$i1++;
			}
			else if($x[0] === "aVmin" . $i2)
			{
				$aVmin[$i2] = $x[1];
				$i2++;
			}
			else if($x[0] === "aMax" . $i3)
			{
				$aVmax[$i3] = $x[1];
				$i3++;
			}
			else if($x[0] === "aRez" . $i4)
			{
				$aRez[$i4] = $x[1];
				$i4++;
			}
			else if($x[0] === "aUma" . $i5)
			{
				$aUma[$i5] = $x[1];
				$i5++;
			}
		}
    fclose($handle);
?>
Laborator de Analize  Medicale Dr. ADINA PREDA <br>
ALEXANDRIA, Str. Libertatii Nr. 122-124 <br>
Telefon/Fax: 0347804419 Mobil: 0740371897 <br>
E-mail: adinapreda@gmail.com <br>

<?php
	for($i = 0; $i < $i1; $i++)
	{
	}

	} 
	else 
	{
    }
else:


?>

Aici va puteti vedea rezultatele analizelor folosind CNP-ul dumneavoastra si ID-ul primit. Introduceti-le mai jos.
<br><br>
<form action = 'rezultate.php' method = 'GET'>
CNP: <input type = 'text' name = 'CNP'></input><br><br>
ID: &nbsp;&nbsp;&nbsp;&nbsp;<input type = 'text' name = 'ID'></input><br><br>
<input type = 'submit' value = 'OK'></input>
</form>
</center>

<?php 
	endif; 
?>
</body>
</html>