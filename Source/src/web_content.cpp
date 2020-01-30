#include <ESP8266WebServer.h>
#include "definitions.h"

//<i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
//<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
const char* PROGMEM page_content = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: left;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .ds-labels{
      font-size: 1.5rem;
      vertical-align: middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <span class="iconify" data-icon="flat-color-icons:electrical-sensor" data-inline="false"></span> 
  <h2>%HOSTNAME%</h2>
  <p>
    <img src=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABoAAAAaCAYAAACpSkzOAAAABmJLR0QA/wD/AP+gvaeTAAABMUlEQVRIie2UsUoDQRRFj6t1IKAYWzWL/2Fl0A/Qv/EfJJUkpNVKEUsbCw2oHxCttEgTrVNE12LukMAmM7PjpPPCZdi3+97ZmfcYCFcdOAMGchvYqpAfpA3gHSiAiVwAH8B6SlBPhS+AmnypWDcl6EtFN2diDcU+U4IKOTReUpYIbJ/vU4NcPzBXa4kAK74PUu9o6aD/Hi1PIaAdrZOAb6KVA0PM2Z8rVmfafOsh0IyFrAJ9FTrF9GEPuJsDKoBH5VRWSwVuBTkBxgsg1gcxoI6S94FD4NsDmT3eklzjva31GXig2uCU5Eq279qY3oRoYY9coDetx4EQgNcY0HUFgNVVRA4Z8IJ/AKyf+MNNkwOjAMgI2I2FWDUxk+faifdW8N66UgYcybliA0wfb4AfX4Ff7/ZvKrsthI8AAAAASUVORK5CYII=>
    <span class="ds-labels">Temperature: </span> 
    <span id="temperature">%TEMPERATURE%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <span><img src=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABoAAAAaCAYAAACpSkzOAAAABmJLR0QA/wD/AP+gvaeTAAACmUlEQVRIia3WXYjPWRgH8A+tGjExQ+wOuVHeLshLi9qMLYoU2rhy490NSimilZcLbu2295tCKyFXYi6QkllmuJK8JOOCZq0xXhKZcXGev/9vfv7/3/yn5lun8zvnPM/5Puc553vOb4jqaMRqrMQ0TIz+F7iHS/gH3QVzFGI49uMNevspr/E7hg2UZAJuZya6jM2YihFRpmATWjJ2tzBpICQd4fgAi2rw+QWPw+dxzFGI4ZmVXEND9I/DEbTjnbQf7TiI8WEzCjfD91/8UES0P7OSEskadOI45ktpq8cC/ImXWBu2o/Ek5thXjaQRXWFUStcaPMOsguBmS6k+gXVYHHP8H0F9h43KG09KV2c/JPU4kAlwd/RfjfbmvMNQSSdwJuodOCVpJY867JI2/pB0rG9kVnAy6iWVonsQUUyN9l38nLNZgef4pHykOzBH2rO2sPspSOZXIuoOx/pMe2TOpnTsS+UmfoyxUVIKC1HpKA7px6cDv+JjtHukLShhfdR/5x0rpS6/9OVB8AzLcmMLlVM3WdLbu/jug/NBtCXahyWd1Iq/JAEPxXXl9F7Xd6U2xMCVaI+VxDi3BpJ5YTsGO2Oe0p73Rt83NCjroTn6VuFsDURnJXmMxispvXcyRK9i7Bv2xcCTWNFAcSz8t+srgV4czRrWSRdiKbeNAyBpwnvpsv0tR9IbY01Zh+wz8VA6wrWglI3V+KMCUcWLdgJaMwYt2IrpkohHYga2YWb4tOKppL+2KkStlSKsw17pmS56xueE/Vucju+uKrZvi1LSIKn8HO6H8YeI/rx0r5FO1gVJM5+rEP1XRFQrLkraGYNHVYguDAZRs3TftQRpnuSL9G8xKNgTZD05kh7lR3HQsFS6xrqjXJZ5AL8CUBvnK2wA5lkAAAAASUVORK5CYII=></span>
    <span class="ds-labels">Humidity: </span>
    <span id="humidity">%HUMIDITY%</span>
    <sup class="units">%</sup>
  </p>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 10000) ;
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 10000) ;
</script>
</html>)rawliteral";