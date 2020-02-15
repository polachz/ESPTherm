#include <ESP8266WebServer.h>
#include "definitions.h"

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
    
    img.middle { 
       vertical-align: middle;
    }
    .host-name {
        font-size: 1.6rem;
        vertical-align: middle;
        font-weight: bold;
    }
    .main-date {
       margin-top: 25px;
       font-size: 0.9rem;
    }
    .current-div{
       margin-bottom: 1px;
    }
    .current-label{
      font-size: 1.5rem;
      vertical-align: middle;
      font-weight: normal;
    }
    .current-value {
        font-size: 2.0rem;
        vertical-align: middle;
        font-weight: normal;
        padding-left: 5px;
    }
    .current-unit {
        margin-left: -3px;
        top: -0.3em;
        font-size: 1.2rem;
        font-weight: normal; 
    }
    .div-min {
        padding-left: 35px;
    }
    .div-max {
        padding-left: 35px;
        margin-bottom: 30px;
    }
    .minmax-label {
       font-size: 1.1rem;
    }
    .min-value {
       font-size: 1.1rem;
       padding-left: 5px;
    }
    .max-value {
       font-size: 1.1rem;
    }
    .minmax-unit {
       top: -0.2em;  
       font-size: 0.8rem;
       margin-left: 2px;
    }
    .minmax-date {
       font-size: 0.7rem;
    }
    span.mini-calendar::before {
        padding-left: 20px;
        content: url(data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAoAAAAKCAQAAAAnOwc2AAAABGdBTUEAALGPC/xhBQAAACBjSFJNAAB6JgAAgIQAAPoAAACA6AAAdTAAAOpgAAA6mAAAF3CculE8AAAAAmJLR0QAAKqNIzIAAAAJcEhZcwAADsQAAA7EAZUrDhsAAAAHdElNRQfkAg8QGQDkhLpqAAAApklEQVQI1zXBvUoCAQAA4O/+IkS7cPEGFYQgCEqirQcQfIB7hmjtJXTzDZydHBxceoyosSAiOHJLLqzzZ+r7ApmBoaVrf54NLT1GRs50/eo5lTjXcBvreHDsVWbnS8+PSWyrVElVOLG2sQuRaKpLNdS1RV5i//be5a4UZjG2Shvkbqw03YX2Iqmalr6FwIdu6Ejq07c3hUtzpTIwdqESejJzr2NtegBcdyyPFi2sXwAAACV0RVh0ZGF0ZTpjcmVhdGUAMjAyMC0wMi0xNVQxNjoyNDo0NiswMDowMA4gaoYAAAAldEVYdGRhdGU6bW9kaWZ5ADIwMjAtMDItMTVUMTY6MjQ6NDYrMDA6MDB/fdI6AAAAGXRFWHRTb2Z0d2FyZQB3d3cuaW5rc2NhcGUub3Jnm+48GgAAAABJRU5ErkJggg==);
}   }
  </style>
</head>
<body>
    <div><img class="middle" src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACQAAAAkCAYAAADhAJiYAAAABmJLR0QA/wD/AP+gvaeTAAAECklEQVRYhe3YT4jVVRQH8M+MOiOZZVQ6zZhSg5EFtXBRLovatKjQGc0CK4wxMaU/UNS2MKEgWphhRqhZikgWQpqFghm6K2sl7TItZ9Iio7TstTjn5/vNc97zvSmhhV+43N+7v3PP/f7OOfecex8X0RhtDd71oPMCrXsK3zcj2I5nMITKBW5DeDrXPIuxNYSewitYi934q8kvbhVjcSdeTXKv1RMcwpoWFLehC7dm69I4DGqxFsdqmRa4Blfis/MoGYd5uBdX4CiO5Lvu1HMcH2EL/myg61MsyjlHa19OF+ab00DBPOzBUkwujY/PVmAynkjZuQ30zck1pxcD7fVlh6FDuPIW3IMN6Mcnws2/ZxvCTvRhXcrOwmph2ZZQz0Id+FD1S5dgUAT8XryYY0vy+XOcEbGxOOf0YdsIpM6xUDOE1iSZTmGZCjbiugYf14tNKbs+5/YJS/0rQv14KZ83iIT2SP4eg/l4HweyvSfibEzKLMo56/L3CsNjqiVC40RQXiLcUSmRuRnfqJ/0vsbMEqkKBjAhdRaua4nQQ2I3XSbiYWOO34QTKfsrVmFhtjdwMt+dKJHajB8xEcuwYDSENovtu1QE8PXCFYVlvsTUEfRMw8GUOZhzekWgLxHJc1OrhNrFlpb93nyeX7JMmcykbAWuVbVUf47tw4583pVrNJ2HrlbNvrOE3+G+7NfjcD4/h59EDno2x74Tm6A8Z0/qIrLyVSMtXI9QkcrHi/JQHBV6sz+Q/SSxc9qFa1aoWmp/9jOyPyxKU6f42O5WCLWCyn+g4yzqEToqvuAPUSh7cvzb7G/P/me8IAL2DJ7PMZid/aHspwrXnkrdRUjURb2g3inKAZH0KiJgp5XmTsLlNbp+S9m+HPsCH+fzLnFMaTqo/xZ5ZIqoY7NF/GwV234CtovdRFjllxKZ7SKhHsQHIo5uS11dqifShqjNQw+KI8REkdSK3DFTNTGeFPVpIR7Gm6qWOY4bc84W/JC6luOBHB916Vic7xaVSBXJb6T2VYnMQI49Jiy7W/Vg2HJxnSu2MlEgT5VIjRFJb6PY4vvxroiZIhQGcBrv5O+VuL+kf1THj9W5SGeSqoiy0qs+Zgg3VZJMh9gQq2rkziFUe+sYCctTOREn+8RB7JCwyh7VxNmDO0QADwoLvZVkFmTfNBqdqccJS60QMTVRFMod4iRQxM4xsbUfx6UiZlYKy4x0hB2Vy8qYKyyyTKSEAp2G33K7hGV3Gx4z5yVUdtnp7BsdxreK600fXhcF8ohwWZvIwN3CXdtwt8aXzY6atc/BoPB5K5iielGcch7ZWrytwUURXhbX2zZxYWz1Kn1Dk3JjcRceFff7umgT9/tBF/7PhmN4Us3V+3//d8xF1OIfWMBQStZ2MIAAAAAASUVORK5CYII=">
    <span id="host_name" class="host-name">%HOSTNAME%</span></div>
  
    <div style="margin-top: 20px; margin-bottom: 20px; padding-left: 35px;" >
    <img class="middle" src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAQAAAC1+jfqAAAABGdBTUEAALGPC/xhBQAAACBjSFJNAAB6JgAAgIQAAPoAAACA6AAAdTAAAOpgAAA6mAAAF3CculE8AAAAAmJLR0QAAKqNIzIAAAAJcEhZcwAADsQAAA7EAZUrDhsAAAAHdElNRQfkAg0MAgNrjrLVAAABGUlEQVQoz3XPvyvEARgG8I9LjoGTwqD8uMTATSJlMYlBVyQxmUQsZJCZlJSSUv4BZVQMREoG6bZLhlsY/Cz5EbqoM9z3BuR5632e3vfpeXvJYsMEWDIHpq1mF3kKzejQ6lUKMZ8u0KBIwonlfGu6bWp0J4EqaQmUikgaU82zPkzqASMGQNwo+j2R0ek/dMqEAhn6p+fIunGk1GuSxJSVXEz2REQYFaAchUrQ4Cw/sFV6cq/Ooy8PogYVO7WtNZcwbxiHajHkzbkj73aF/34R9WZazIyoKws5w4B2zCkz6xxjbrQYdx3yGxH3SHoRd6uUtK4fhrh30UBvOcizr8Cir2B0KWVHs0W3hvRqo8aetExQxwhbcO3DgRjfJNJRzYwLO+8AAAAldEVYdGRhdGU6Y3JlYXRlADIwMjAtMDItMTNUMTI6MDI6MDMrMDA6MDAeCIEvAAAAJXRFWHRkYXRlOm1vZGlmeQAyMDIwLTAyLTEzVDEyOjAyOjAzKzAwOjAwb1U5kwAAABl0RVh0U29mdHdhcmUAd3d3Lmlua3NjYXBlLm9yZ5vuPBoAAAAASUVORK5CYII=">
    <span class="main-date" id="date">%DATE_TIME%</span>
    </div>
  
    <div class="current-div">
    <img class="middle" src=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABoAAAAaCAYAAACpSkzOAAAABmJLR0QA/wD/AP+gvaeTAAABMUlEQVRIie2UsUoDQRRFj6t1IKAYWzWL/2Fl0A/Qv/EfJJUkpNVKEUsbCw2oHxCttEgTrVNE12LukMAmM7PjpPPCZdi3+97ZmfcYCFcdOAMGchvYqpAfpA3gHSiAiVwAH8B6SlBPhS+AmnypWDcl6EtFN2diDcU+U4IKOTReUpYIbJ/vU4NcPzBXa4kAK74PUu9o6aD/Hi1PIaAdrZOAb6KVA0PM2Z8rVmfafOsh0IyFrAJ9FTrF9GEPuJsDKoBH5VRWSwVuBTkBxgsg1gcxoI6S94FD4NsDmT3eklzjva31GXig2uCU5Eq279qY3oRoYY9coDetx4EQgNcY0HUFgNVVRA4Z8IJ/AKyf+MNNkwOjAMgI2I2FWDUxk+faifdW8N66UgYcybliA0wfb4AfX4Ff7/ZvKrsthI8AAAAASUVORK5CYII=>
    <span class="current-label">Temperature: </span>
    <span class="current-value" id="temperature">%TEMPERATURE%</span>
    <sup class="current-unit">&deg;C</sup>
    </div>
     <div class="div-min" >
     <span class="minmax-label">Min: </span>
     <span class="min-value" id="temperatureMin">%TEMPERATURE_MIN%</span><sup class="minmax-unit">&deg;C</sup>
     <span class="mini-calendar"></span>
     <span class="minmax-date" id="temperatureMinDate">%TEMPERATURE_MIN_TS%</span>
    </div>
    <div class="div-max" >
     <span class="minmax-label">Max: </span>
     <span class="max-value" id="temperatureMax">%TEMPERATURE_MAX%</span><sup class="minmax-unit">&deg;C</sup>
     <span class="mini-calendar"></span>
     <span class="minmax-date" id="temperatureMaxDate">%TEMPERATURE_MAX_TS%</span>
    </div>
   
    <div class="current-div">
    <img class="middle" src=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABoAAAAaCAYAAACpSkzOAAAABmJLR0QA/wD/AP+gvaeTAAACmUlEQVRIia3WXYjPWRgH8A+tGjExQ+wOuVHeLshLi9qMLYoU2rhy490NSimilZcLbu2295tCKyFXYi6QkllmuJK8JOOCZq0xXhKZcXGev/9vfv7/3/yn5lun8zvnPM/5Puc553vOb4jqaMRqrMQ0TIz+F7iHS/gH3QVzFGI49uMNevspr/E7hg2UZAJuZya6jM2YihFRpmATWjJ2tzBpICQd4fgAi2rw+QWPw+dxzFGI4ZmVXEND9I/DEbTjnbQf7TiI8WEzCjfD91/8UES0P7OSEskadOI45ktpq8cC/ImXWBu2o/Ek5thXjaQRXWFUStcaPMOsguBmS6k+gXVYHHP8H0F9h43KG09KV2c/JPU4kAlwd/RfjfbmvMNQSSdwJuodOCVpJY867JI2/pB0rG9kVnAy6iWVonsQUUyN9l38nLNZgef4pHykOzBH2rO2sPspSOZXIuoOx/pMe2TOpnTsS+UmfoyxUVIKC1HpKA7px6cDv+JjtHukLShhfdR/5x0rpS6/9OVB8AzLcmMLlVM3WdLbu/jug/NBtCXahyWd1Iq/JAEPxXXl9F7Xd6U2xMCVaI+VxDi3BpJ5YTsGO2Oe0p73Rt83NCjroTn6VuFsDURnJXmMxispvXcyRK9i7Bv2xcCTWNFAcSz8t+srgV4czRrWSRdiKbeNAyBpwnvpsv0tR9IbY01Zh+wz8VA6wrWglI3V+KMCUcWLdgJaMwYt2IrpkohHYga2YWb4tOKppL+2KkStlSKsw17pmS56xueE/Vucju+uKrZvi1LSIKn8HO6H8YeI/rx0r5FO1gVJM5+rEP1XRFQrLkraGYNHVYguDAZRs3TftQRpnuSL9G8xKNgTZD05kh7lR3HQsFS6xrqjXJZ5AL8CUBvnK2wA5lkAAAAASUVORK5CYII=>
    <span class="current-label" style= "margin-left: 4px;">Humidity: </span>
    <span class="current-value" id="humidity">%HUMIDITY%</span>
    <sup class="current-unit">%</sup>
    </div>
     <div class="div-min" >
     <span class="minmax-label">Min: </span>
     <span class="min-value" id="humidityMin">%HUMIDITY_MIN%</span><sup class="minmax-unit">%</sup>
     <span class="mini-calendar"></span>
     <span class="minmax-date" id="humidityMinDate">%HUMIDITY_MIN_TS%</span>
    </div>
    <div class="div-max" >
     <span class="minmax-label">Max: </span>
     <span class="max-value" id="humidityMax">%HUMIDITY_MAX%</span><sup class="minmax-unit">%</sup>
     <span class="mini-calendar"></span>
     <span class="minmax-date" id="humidityMaxDate">%HUMIDITY_MAX_TS%</span>
    </div>
</body>
<script>
   function update_values(){
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
                var arr =  this.responseText.split(",") ;
                //var dtt = new Date();
                //var casik = parseInt(arr[1]);
                //dtt.setTime(casik);
                document.getElementById("host_name").innerHTML = arr[0];
                //document.getElementById("date").innerHTML = dtt.toLocaleString("cs-CZ");
                document.getElementById("date").innerHTML = arr[1];
                document.getElementById("temperature").innerHTML = arr[2];
                document.getElementById("temperatureMin").innerHTML = arr[3];
                document.getElementById("temperatureMinDate").innerHTML = arr[4];
                document.getElementById("temperatureMax").innerHTML = arr[5];
                document.getElementById("temperatureMaxDate").innerHTML = arr[6];
                document.getElementById("humidity").innerHTML = arr[7];
                document.getElementById("humidityMin").innerHTML = arr[8];
                document.getElementById("humidityMinDate").innerHTML = arr[9];
                document.getElementById("humidityMax").innerHTML = arr[10];
                document.getElementById("humidityMaxDate").innerHTML = arr[11];
            }
        };
    xhttp.open("GET", "/gwv", true);
    xhttp.send(); 
   }
   function init_page(){
       update_values();
       setInterval("update_values()", 5000);
   }
   
   init_page();

</script>
</html>
 )rawliteral";