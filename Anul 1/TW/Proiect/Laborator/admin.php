<?php
session_start();

include './includes/pass.php';
if($_SESSION['admin'] != $adminpass && $_POST['pass'] != $adminpass)
{
	header('Location: adminver.php');
	exit();
}

?>

<html>
<head>

<script type = 'text/javascript'>

var currentId = -1;

function showText(text)
{
	alert(text);
}

function accept(id)
{
	if(currentId != -1) document.getElementById('tr' + currentId).style.backgroundColor = '00FFCC';
	currentId = id;
	document.getElementById('tr' + id).style.backgroundColor = 'FF9900';
	document.getElementById("input").style.visibility = "visible";
	document.getElementById("inputHour").value = "";
	document.getElementById("inputMin").value = "";
	document.getElementById("inputDay").value = "";
	document.getElementById("inputMonth").value = "";
	document.getElementById("inputYear").value = "";
	document.getElementById("inputAlte").value = "";
}

function accept2()
{
	var id = currentId;
	var code = document.getElementById('code' + id).innerHTML;
	var hour = document.getElementById('inputHour').value + ":" + document.getElementById('inputMin').value;
	var date = document.getElementById('inputDay').value + "/" + document.getElementById("inputMonth").value + "/" + document.getElementById("inputYear").value;
	var alte = document.getElementById("inputAlte").value;
	if(hour.length < 5 || 
	   parseInt(document.getElementById('inputHour').value) > 24 || 
	   parseInt(document.getElementById('inputMin').value) > 60 || 
	   isNaN(document.getElementById('inputHour').value) ||
	   isNaN(document.getElementById('inputMin').value) )  
	{
		alert("Completeaza corect ora si minutul programarii. \nExemplu: 08:00");
		return;
	}
	if(date.length < 10 || 
	   parseInt(document.getElementById('inputDay').value) > 31 ||
	   parseInt(document.getElementById('inputMonth').value) > 12 || 
	   parseInt(document.getElementById('inputYear').value) < 2014 ||
	   isNaN(document.getElementById('inputDay').value) ||
	   isNaN(document.getElementById('inputMonth').value) ||
	   isNaN(document.getElementById('inputYear').value) ) 
	{
		alert("Completeaza corect data programarii. \nExemplu: 18/08/2014 (zi / luna / an)");
		return;
	}
	var xmlhttp;
	if(window.XMLHttpRequest) xmlhttp=new XMLHttpRequest();
	else xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	xmlhttp.onreadystatechange=function()
	{
		if (xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			document.getElementById('tr' + id).style.backgroundColor = 'FF6666';
			document.getElementById('button' + id).innerHTML = 'Respinge';
			document.getElementById('button' + id).onclick = function() { respinge(id) };	
		}
	}
	xmlhttp.open("GET","accept.php?code=" + code + "&hour=" + hour + "&date=" + date + "&alte=" + alte,true);
	xmlhttp.send();
	document.getElementById("input").style.visibility = "hidden";
}

function respinge(id)
{
	var code = document.getElementById('code' + id).innerHTML;
	var xmlhttp;
	if(window.XMLHttpRequest) xmlhttp=new XMLHttpRequest();
	else xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	xmlhttp.onreadystatechange=function()
	{
		if (xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			document.getElementById('tr' + id).style.backgroundColor = '00FFCC';
			document.getElementById('button' + id).innerHTML = 'Accept';
			document.getElementById('button' + id).onclick = function() { accept(id) };
		}
	}
	xmlhttp.open("GET","respinge.php?code=" + code,true);
	xmlhttp.send();
}

</script>
</head>
<body>

	<div id = 'programari'>
		<table border = 1>
			<tr>	
				<th>Code:</th>
				<th>Nume:</th>
				<th>Prenume:</th>
				<th>CNP:</th>
				<th>Telefon:</th>
				<th>Mail:</th>
				<th>Trimitere:</th>
				<th>Liber:</th>
				<th>Altceva:</th>
				<th>Accept:</th>
			</tr>
			
			<?php
		
				include './includes/connection.php';
				$result = mysqli_query($con, "SELECT Code, Nume, Prenume, CNP, Phone, Mail, Trimitere, Liber, Alte, Accept FROM programari ORDER BY Timestamp DESC Limit 15");
				$id = 0;
				while($row = mysqli_fetch_row($result))
				{
					echo '<tr id = \'tr' . $id . '\' style = "background:';
					if($row[9] == 1) echo 'FF6666">';
					else echo '00FFCC">';
					$i = 0;
					while($i < count($row) - 1)
					{
						if($i == 6)
						{
							if($row[6] == 0) echo "<td>Nu</td>";
							else echo "<td>Da</td>";
						}
						else if($i == 4)
						{
							echo '<td>0' . $row[$i] . '</td>';
						}
						else if($i == 7 || $i == 8)
						{
							if(strlen($row[$i]) > 1) echo "<td><button type = 'button' onclick = 'showText(\"$row[$i]\")'>Citeste</button></td>";
							else echo "<td>Nimic</td>";
						}
						else if($i == 0)
						{
							echo "<td id = 'code$id' >$row[$i]</td>";
						}
						else echo "<td>$row[$i]</td>";
						$i++;
					}
					if($row[9] == 0) echo "<td><button id = 'button$id' type = 'button' onclick = 'accept($id)'>Accept</button></td>";
					else echo "<td><button id = 'button$id' type = 'button' onclick = 'respinge($id)'>Respinge</button></td>";
					echo '</tr>';
					$id++;
				}
		
				mysqli_free_result($result);
	
				?>
		</table>
		<br><br>
		Rosu = acceptata<br>
		Verde = neacceptata<br>
	</div>
	
	<div id = "input" style = "position: fixed; left:300px; width:300px; height:200px; background-color:white; visibility:hidden">
	Ora programarii: <input type = "text" id = "inputHour" style = "width:28px;" maxlength = 2 placeholder = "hh"></input> : <input type = "text" id = "inputMin" style = "width:28px;" maxlength = 2 placeholder = "mm"></input><br><br>
	Data programarii: <input type = "text" id = "inputDay" style = "width:28px;" maxlength = 2 placeholder = "dd"></input> / <input type = "text" id = "inputMonth" style = "width:28px;" maxlength = 2 placeholder = "mm"> / <input type = "text" id = "inputYear" style = "width:35px;" maxlength = 4 placeholder = "yyyy"></input></input><br>
	Alte detalii: <textarea id = "inputAlte" style = "position: relative; top:21px; width:200px; height:40px;"></textarea><br>
	<center><button onclick = "accept2()" style = "position: relative; top:30px;">Accept</button></center>
	</div>
</body>
</html>