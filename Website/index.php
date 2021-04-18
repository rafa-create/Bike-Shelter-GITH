<?php
//require_once 'Place.php';
$Aplaces=file_get_contents(__DIR__.DIRECTORY_SEPARATOR."places.txt");
$heures= date('H')+2 ;
$minutes=date('i');
//Place:: 
?>

<!DOCTYPE html>
<html lang="fr">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="https://unpkg.com/leaflet@1.3.1/dist/leaflet.css" integrity="sha512-Rksm5RenBEKSKFjgI3a41vrjkw4EVPlJ3+OiI65vTjIdo9brlAacEuKOiQ5OFh7cOI1bkDwLqdLw3Zg0cRJAAQ==" crossorigin="" />
    <link rel="shortcut icon" type="image/png" href="/image/logo.png"/>
    <title>Abri vélos</title>
    <link rel="stylesheet" href="css/styles.css">
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/font-awesome@4.7.0/css/font-awesome.min.css">
</head>

<body>
    <section class="top-page">
        <header class="header">
            <img src="image/logo.png" alt="Logo du site">
            <a class="big-title"> Abri vélos</a>
        </header>    
    </section>
    <div id="map"></div>
    <a type="button" id="locate-position" onClick="javascript:getLocationLeaflet();" title="Me localiser"><i class="fa fa-map-marker" aria-hidden="true" ></i></a>     
    <footer>
        <p class="copyright">&copy; 2021 - ENSEM </p>
        <a href="contact.html" class="cgv">Contact</a>
    </footer>
    <script src="https://unpkg.com/leaflet@1.3.1/dist/leaflet.js" integrity="sha512-/Nsx9X4HebavoBvEBuyp3I7od5tA0UzAxs+j83KgC8PU0kgB4XiK4Lfe4y4cgBtaRJQEIFCW+oC506aPT2L1zw==" crossorigin=""></script>
	<script type="text/javascript">
            // On initialise la latitude et la longitude 
            var lat = 48.65322;
            var lon = 6.14777;
            var macarte = null;
            function initMap() {
                // Créer l'objet "macarte" et l'insèrer dans l'élément HTML qui a l'ID "map"
                macarte = L.map('map').setView([lat, lon], 16);
                // Leaflet ne récupère pas les cartes (tiles) sur un serveur par défaut. Nous devons lui préciser où nous souhaitons les récupérer. Ici, openstreetmap.fr
                L.tileLayer('https://{s}.tile.openstreetmap.fr/osmfr/{z}/{x}/{y}.png', {
                    // Il est obligatoire de laisser le lien vers la source des données :  Open Database License 
                    attribution: '© <a href="https://www.openstreetmap.org/copyright">OSM</a>',
                    minZoom: 1,
                    maxZoom: 20
                }).addTo(macarte);
                // marquer
                var marker = L.marker([lat, lon]).addTo(macarte);
                L.marker([lat-0.00201, lon-0.00301]).addTo(macarte)
                .bindPopup('<b><a href="https://goo.gl/maps/UeHD5ghRZWAA1zsd6">Abri fictif 1 :</a></b><br><b>0 place libre</b><br><i>Actualisé à <?= $heures;?>h<?= $minutes;?></i>')
                L.marker([lat-0.00403, lon-0.00301]).addTo(macarte)
                .bindPopup('<b><a href="https://goo.gl/maps/UeHD5ghRZWAA1zsd6">Abri fictif 2 :</a></b><br><b>0 place libre</b><br><i>Actualisé à <?= $heures;?>h<?= $minutes;?></i>')
                L.marker([lat-0.00403, lon]).addTo(macarte)
                .bindPopup('<b><a href="https://goo.gl/maps/UeHD5ghRZWAA1zsd6">Abri fictif 3 :</a></b><br><b>0 place libre</b><br><i>Actualisé à <?= $heures;?>h<?= $minutes;?></i>')
                L.marker([lat, lon]).addTo(macarte)
                .bindPopup('<b><a href="https://goo.gl/maps/UeHD5ghRZWAA1zsd6">Brabois-Ingénierie :</a></b><br><b><?= $Aplaces;?> places libres</b><br><i>Actualisé à <?= $heures;?>h<?= $minutes;?></i>')
                .openPopup();
            }
            var loc = new L.circle();
            function onLocationFound(e) {
                macarte.removeLayer(loc);
                var radius = e.accuracy / 2;
                var location = e.latlng;
                loc = new L.circle(location, radius).addTo(macarte);
                macarte.addLayer(loc);
            }
            function onLocationError(e) {
            alert(e.message);
            }
            function getLocationLeaflet() {
            macarte.on('locationfound', onLocationFound);
            macarte.on('locationerror', onLocationError);
            macarte.locate({setView: true, maxZoom: 16});
            }
            window.onload = function(){
		    initMap(); 
            };
    </script>
</body>
</html>