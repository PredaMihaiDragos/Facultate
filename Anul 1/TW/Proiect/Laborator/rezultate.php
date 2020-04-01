<html>
<head>
<style>
th, td 
{
    border: 1px solid black;
    border-collapse: collapse;
}
table
{
	border-collapse: collapse;
}
</style>
</head>
<body>



<center> <img id = 'title' src = './images/rezultateTitle.png'> </img> </center>
<br><br>

<?php

if(!empty($_GET['CNP']) && !empty($_GET['ID'])):
	$idp = $_GET['CNP'];
	$tempid = str_replace(' ', '', $_GET['ID']);
	
	$id = explode("-", $tempid);
	$cuv = $id[0];
	$codv = $id[1];
	require_once 'dbfReader.php';
	
	$bilet = new dbf("database/bilet.DBF");
	$pacient = new dbf("database/pacient.DBF");
	$doctor = new dbf("database/doctor.DBF");
	$lbilet = new dbf("database/lbilet.DBF");
	$lbilete = new dbf("database/lbilete.DBF");
	$grupe = new dbf("database/grupe.DBF");
	
	$r = -1;
	$records = $bilet->getMultipleRecords("CODV", $codv);
	for($i = 0, $n = count($records); $i < $n; $i++)
	{	
		if($bilet->getField($records[$i], "CUV") === $cuv &&
		   $bilet->getField($records[$i], "IDP") === $idp)
		{
		//	if($bilet->getField($records[$i], "GATA") !== 'T') echo("<script>window.location = 'http://laboratorpreda.ro.tn/rezultate.php?error=gata'</script>");
			$r = $records[$i];
			break;
		}
	}
	if($r == -1): echo("<script>window.location = 'http://laboratorpreda.ro.tn/rezultate.php?error=id'</script>");
	else:
	$name = $pacient->getField($pacient->getRecord("IDP", $idp), "NP");
	if($idp[0] == '1')
	{
		$sex = 'M';
		$nastere[0] = '1' . '9' . $idp[1] . $idp[2];
		$nastere[1] = $idp[3] . $idp[4];
		$nastere[2] = $idp[5] . $idp[6];
	}
	else if($idp[0] == '2')
	{
		$sex = 'F';
		$nastere[0] = '1' . '9' . $idp[1] . $idp[2];
		$nastere[1] = $idp[3] . $idp[4];
		$nastere[2] = $idp[5] . $idp[6];
	}
	else if($idp[0] == '5')
	{
		$sex = 'M';
		$nastere[0] = '2' . '0' . $idp[1] . $idp[2];
		$nastere[1] = $idp[3] . $idp[4];
		$nastere[2] = $idp[5] . $idp[6];
	}
	else if($idp[0] == '6')
	{
		$sex = 'F';
		$nastere[0] = '2' . '0' . $idp[1] . $idp[2];
		$nastere[1] = $idp[3] . $idp[4];
		$nastere[2] = $idp[5] . $idp[6];
	}
	$today = date("y-m-d");  
	$today = '20' . $today;
	$date1= new DateTime("$nastere[0]-$nastere[1]-$nastere[2]");
	$date2= new DateTime($today);
	$diff= $date1->diff($date2);
	$varsta = $diff->format('%y ani,%m luni,%d zile');
	
	$db = $bilet->getField($r, "DB");
	$db = substr_replace($db, "/", 4, 0);
	$db = substr_replace($db, "/", 7, 0);
	$temp = explode("/", $db);
	$db = $temp[2] . '/' . $temp[1] . '/' . $temp[0];
	
	$rec = $bilet->getField($r, "RECEXT");
	$trm = $bilet->getField($r, "TRIMIS");
	$orap = $bilet->getField($r, "ORAPREZ");
	//$orar = $bilet->getField($r, "ORARECOLTA");
	$pard = trim($bilet->getField($r, "PARD"), " ");
	if(strlen($pard) > 1) $doc = $doctor->getField($doctor->getRecord("PARD", $pard), "ND");
	else $doc = " ";
	
	$codgs = array();
	
	$records = $lbilet->getMultipleRecords("CODV", $codv);
	$aDen  = array();
	$aVmin = array();
	$aVmax = array();
	$aRez  = array();
	$aUma  = array();
	$aCoda = array();
	$aCodg = array();
	
	$sDen  = array();
	$sVmin = array();
	$sVmax = array();
	$sRez  = array();
	$sUma  = array();
	
	$n = count($records);
	for($i = 0; $i < $n; $i++)
	{
		if($lbilet->getField($records[$i], "CUV") !== $cuv)
		{
			$x = $lbilet->getField($records[$i], "CUV");
			echo "alert($x);";
			continue;
		}
		array_push($aDen,  $lbilet->getField($records[$i], "DENA"));
		array_push($aVmin, $lbilet->getField($records[$i], "VMINA"));
		array_push($aVmax, $lbilet->getField($records[$i], "VMAXA"));
		array_push($aRez,  $lbilet->getField($records[$i], "REZULTAT"));
		array_push($aUma,  $lbilet->getField($records[$i], "UMA"));
		array_push($aCoda, $lbilet->getField($records[$i], "CODA"));
		$codg = $lbilet->getField($records[$i], "CODG");
		array_push($aCodg, $codg);
		if(!in_array($codg, $codgs)) array_push($codgs, $codg);
		
		array_push($sDen,  array());
		array_push($sVmin, array());
		array_push($sVmax, array());
		array_push($sRez,  array());
		array_push($sUma,  array());
		
	}
	
	$records = $lbilete->getMultipleRecords("CODV", $codv);
	for($i = 0, $n = count($records); $i < $n; $i++)
	{
		if($lbilete->getField($records[$i], "CUV") !== $cuv) continue;
		$coda = $lbilete->getField($records[$i], "CODA");
		for($q = 0, $x = count($aDen); $q < $x; $q++)
		{
			if($coda === $aCoda[$q])
			{
				array_push($sDen[$q],  $lbilete->getField($records[$i], "CODE"));
				array_push($sVmin[$q], $lbilete->getField($records[$i], "VMINE"));
				array_push($sVmax[$q], $lbilete->getField($records[$i], "VMAXE"));
				array_push($sRez[$q],  $lbilete->getField($records[$i], "REZULTATE"));
				array_push($sUma[$q],  $lbilete->getField($records[$i], "UME"));
				break;
			}
		}
	}
?>
Laborator de Analize  Medicale Dr. ADINA PREDA <br>
ALEXANDRIA, Str. Libertatii Nr. 122-124 <br>
Telefon/Fax: 0347804419 Mobil: 0740371897 <br>
E-mail: adinapreda@gmail.com <br><br>

<img style = "position: absolute; right:5px; top:80px" src = 'images/sigla.jpg'></img>


<center>
<font size = 5>Buletin de Analize  Medicale <?php echo $tempid;?></font>
</center>
<br>

<div style = "border-style:solid; border-width:1px; height:100px;">
Nume: <?php echo $name;?><br>
C.N.P.: <?php echo $idp;?> 
Sex: <?php echo $sex;?> 
Varsta: <?php echo $varsta;?> <br>
Adresa:<br>
Trimis de: <?php echo $doc . " ($pard)";?><br>
Institutia: / Nr.trimitere:<br>

	<span style = "position: relative; left:400px; top:-80px;">
	Data recoltare: <?php echo $db;?> &nbsp;&nbsp;
	Data rezultat: <?php echo $db;?><br>
	Ora recoltarii/prezentarii: <?php echo $orap;?><br>
	Operator: ADINA PREDA<br>
	Punct de recoltare:
	<?php
	if($rec === "T") echo "Extern";
	else echo "Intern";
	?><br>
	</span>

</div>

<br>

<center>
	<table style = "position:relative;">
	<tr>
		<th>Denumire analiza</th>
		<th>Rezultat</th>
		<th>Unitate de masura</th>
		<th>Interval biologic de referinta</th>
	</tr>
	<?php
	sort($codgs, SORT_NUMERIC);
	for($t = 0, $j = count($codgs); $t < $j; $t++)
	{
		$grup = $grupe->getField($grupe->getRecord("CODG", $codgs[$t]), "DENG");
		echo "<td style = 'border-style:none'><b>$grup</b></td>";
		for($i = 0, $n = count($aDen); $i < $n; $i++)
		{
			if($aCodg[$i] != $codgs[$t]) continue;
			echo "<tr>";
			if( (is_numeric($aVmin[$i]) && is_numeric($aVmax[$i]) && is_numeric($aRez[$i]) && (strval($aRez[$i]) < $aVmin[$i] || strval($aRez[$i]) > $aVmax[$i]) ) ||
				substr($aRez[$i], -1) === '!')
			{
				echo "<td><b>$aDen[$i] !</b></td>";
				echo "<td style = 'background-color:#B8B8B8'>$aRez[$i]</td>";
				echo "<td>$aUma[$i]</td>";
				echo "<td>$aVmin[$i] - ";
				echo "$aVmax[$i]</td>";
				echo "</tr>";
			}
			else
			{
				echo "<td>$aDen[$i]</td>";
				echo "<td>$aRez[$i]</td>";
				echo "<td>$aUma[$i]</td>";
				echo "<td>$aVmin[$i] - ";
				echo "$aVmax[$i]</td>";
				echo "</tr>";
			}
			
			$x = count($sDen[$i]);
			if($x != 0)
			{
				for($q = 0; $q < $x; $q++)
				{
					if(strlen($sRez[$i][$q]) < 1) continue;
					$den  = $sDen[$i][$q];
					$rez  = $sRez[$i][$q];
					$uma  = $sUma[$i][$q];
					$vMin = $sVmin[$i][$q];
					$vMax = $sVmax[$i][$q];
					if( (is_numeric($vMin) && is_numeric($vMax) && is_numeric($rez) && (strval($rez) < $vMin || strval($rez) > $vMax) ) ||
						 substr($rez, -1) === '!')
					{
						echo "<tr style = 'color:black'>";
						echo "<td><b>&#8211 $den !</b></td>";
						echo "<td style = 'background-color:#B8B8B8'>$rez</td>";
						echo "<td>$uma</td>";
						echo "<td>$vMin - ";
						echo "$vMax</td>";
						echo "</tr>";
					}
					else
					{
						echo "<tr style = 'color:#404040'>";
						echo "<td>&#8211 $den</td>";
						echo "<td>$rez</td>";
						echo "<td>$uma</td>";
						echo "<td>$vMin - ";
						echo "$vMax</td>";
						echo "</tr>";
					}
				}
			}
		}
	}
	?>
	</table>
</center>

<br>
<font size = 2>
COD FGL-5.8-01 Editia 1/16.06.2014, Revizia 0/16.06.2014<br>

NOTA: Se declara ca raportul de analiza se refera numai la obiectul analizat. Reproducerea sau utilizarea buletinului de analize in alte scopuri decat cele pentru care a fost realizat, fara acordul Laborator de Analize Medicale Dr. ADINA PREDA, este interzisa!<br>
Rezultatele se refera numai la proba analizata. &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; x - Analize neacreditate RENAR<br>
"!" - Valori in afara limitelor admise pentru varsta si sexul respectiv.
</font>

<?php
endif;
else:


?>

<script type = 'text/javascript'>
function okClick()
{
	document.getElementById('content').innerHTML = "Va rog asteptati...";
	document.getElementById('form').submit();
}

</script>

<center>
<div id = 'content'>
Aici va puteti vedea rezultatele analizelor folosind CNP-ul dumneavoastra si ID-ul primit. Introduceti-le mai jos.
<br><br>
<form id = 'form' action = 'rezultate.php' method = 'GET'>
CNP: <input type = 'text' name = 'CNP' maxlength = '13'></input><br><br>
ID: &nbsp;&nbsp;&nbsp;&nbsp;<input type = 'text' name = 'ID' maxlength = '11'></input><br><br>
<input type = 'submit' value = 'OK'></input>
</form>
</div>
</center>



<?php 
	endif; 
	if(!empty($_GET['error']))
	{
		$error = $_GET['error'];
		if($error === 'id')
		{
			echo "<script>alert('Nu s-a gasit niciun bilet. Daca ai introdus datele bine, inseamna ca biletul nu este gata. Incearca mai tarziu.')</script>";
		}
		else if($error === 'gata')
		{
			echo "<script>alert('Biletul introdus este in lucru. Incearca mai tarziu.')</script>";
		}
	}
?>
</body>
</html>