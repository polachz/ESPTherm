
#include <Arduino.h>
#include "debug.h"

#include "config.h"
#include "htu21_sensor.h"
#include "web_server.h"

extern const char* page_content;

/*void on_not_found(AsyncWebServerRequest *request) {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += request->url();
  message += "\nMethod: ";
  message += ( request->method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += request->args();
  message += "\n";
  for ( uint8_t i = 0; i < request->args(); i++ ) {
    message += " " + request->argName ( i ) + ": " + request->arg ( i ) + "\n";
  }
  request->send ( 404, "text/plain", message );
}


void on_root(AsyncWebServerRequest *request)
{
    String message = page_content;
    message.replace("%HOSTNAME%", host_name);
    message.replace("%TEMPERATURE%", GetTemperatureStr());
    message.replace("%HUMIDITY%", GetHumidityStr());
    
    request->send(200, "text/html", message );
    
    //request->send(200, "text/plain", "This is the main server page\n\nNow just testing");   
}
void on_update_web_vals(AsyncWebServerRequest *request)
{
   char buff[100];
   snprintf (buff, sizeof(buff), "%f,%f,%f,%f,%f,%f",
      GetTemperature(), GetTemperatureMax(),GetTemperatureMin(),
      GetHumidity(),GetHumidityMax(),GetHumidityMin()   );\
      request->send(200, "text/plain",buff );

}
void on_temperature(AsyncWebServerRequest *request)
{
    printlnD("/temperature");
    request->send(200, "text/plain", GetTemperatureStr().c_str() );
}

void on_humidity(AsyncWebServerRequest *request)
{
    printlnD("/humidity");
    request->send(200, "text/plain", GetHumidityStr().c_str() );
}

void on_cus(AsyncWebServerRequest *request)
{
    request->send(200, "text/plain", "cus bus autobus");   
}

void on_reset(AsyncWebServerRequest *request)
{
    request->send(200, "text/plain", "Going to reset ESPTherm...");   
    ESP.restart();
}

extern bool doFactoryReset;
void on_factory_reset(AsyncWebServerRequest *request)
{
  printlnI("Erase request received...");
  request->send(200, "text/plain", "Erase request received.\nAll configuration data will be lost!!\nThe ESPTherm will be eerased and rebooted in 2 seconds...");  
  doFactoryReset =true;
printlnD("Reset Request Marked up!");
}
extern bool doResetWlan;
void on_reset_wlan(AsyncWebServerRequest *request)
{
    printlnI("reset_wlan request received...");
    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "Resetting WLAN and restarting..." );
    response->addHeader("Access-Control-Allow-Origin", "*");
    request->send(response);
    doResetWlan=true;
}

extern bool runConfig_ap;
  void on_start_config_ap(AsyncWebServerRequest *request)
  {
    printlnI("configAP request received...");
    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "Starting config AP ..." );
    response->addHeader("Access-Control-Allow-Origin", "*");
    request->send(response);
    runConfig_ap=true;
  }

void web_server_register_handlers(AsyncWebServer& server)
{
    server.onNotFound(on_not_found);
    server.on("/", HTTP_GET, on_root);
    server.on("/updateWebVals", HTTP_GET,on_update_web_vals);
    server.on("/temperature", HTTP_GET,on_temperature);
    server.on("/humidity", HTTP_GET,on_humidity);
    server.on("/cus", HTTP_GET, on_cus);
    server.on("/reset", HTTP_GET, on_reset);
    server.on("/factoryReset", HTTP_GET, on_factory_reset);
    server.on("/resetWlan", HTTP_GET, on_reset_wlan);
    server.on("/startConfigAP", HTTP_GET, on_start_config_ap);

}*/

