<!DOCTYPE html>
<html>
<head>
    <style>
      #map_canvas {
        width: 500px;
        height: 400px;
      }
	  
    </style>
<script src="https://maps.googleapis.com/maps/api/js"></script>
<script>
function initialize() 
{
	var map_canvas = document.getElementById('map_canvas');
	var map_options = {
	  center: new google.maps.LatLng(43.973841, 25.324230),
	  zoom: 18,
	  mapTypeId: google.maps.MapTypeId.ROADMAP
	}
	var map = new google.maps.Map(map_canvas, map_options)
	var marker = new google.maps.Marker({
		position: new google.maps.LatLng(43.973841, 25.324230),
		map: map
	});
}
google.maps.event.addDomListener(window, 'load', initialize);
</script>
<script type = 'text/javascript'>

function hartaClick()
{
	var x = document.getElementById('map_canvas');
	if(x.style.visibility == "hidden") x.style.visibility = 'visible';
	else x.style.visibility = 'hidden';

}

</script>
</head>

<body>

<center> <img id = 'title' src = './images/contactTitle.png'> </img>
<br><br><br>
<font size = 5 color = 'blue'>Numar de telefon: </font><font size = 5 color = 'red'>(0740) 371 897</font><br>
<font size = 5 color = 'blue'>Tel / Fax: </font><font size = 5 color = 'red'>(0347) 804 419</font><br>
<font size = 5 color = 'blue'>Adresa e-mail: </font><font size = 5 color = 'red'>adinapreda@gmail.com</font><br><br>
<font size = 5 color = 'blue'>Adresa laborator: </font><font size = 5 color = 'red'><br>Judetul: Teleorman<br>Orasul: Alexandria<br> Strada: Libertatii, nr. 122 - 124</font><br>
	<button onclick = "hartaClick()">Harta</button>
	<div id="map_canvas" style = "visibility:hidden;"></div>
</center>
</body>
</html>