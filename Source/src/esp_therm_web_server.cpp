#include <Arduino.h>
#include "debug.h"

#include "esp_therm_config.h"
#include "esp_therm_time_date.h"
#include "esp_therm_web_server.h"

using std::placeholders::_1;

void ESPThermWebServer::Setup()
{
    this->onNotFound(std::bind( &ESPThermWebServer::on_not_found, this, _1 ));
    this->on("/", HTTP_GET,std::bind( &ESPThermWebServer::on_root, this, _1 ));
    this->on("/temperature", HTTP_GET,std::bind( &ESPThermWebServer::on_temperature, this, _1 ));
    this->on("/temperature", HTTP_GET,std::bind( &ESPThermWebServer::on_humidity, this, _1 ));

    /*server.on("/updateWebVals", HTTP_GET,on_update_web_vals);
    
    server.on("/cus", HTTP_GET, on_cus);
    server.on("/reset", HTTP_GET, on_reset);
    server.on("/factoryReset", HTTP_GET, on_factory_reset);
    server.on("/resetWlan", HTTP_GET, on_reset_wlan);
    server.on("/startConfigAP", HTTP_GET, on_start_config_ap);*/
    

  //start the server
  this->begin();
}

void ESPThermWebServer::on_not_found(AsyncWebServerRequest *request) {
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

extern const char* page_content;
void ESPThermWebServer::on_root(AsyncWebServerRequest *request)
{
    request->send_P(200, "text/html", page_content, 
      std::bind( &ESPThermWebServer::MainPageProcessor, this, _1 ));
    /*String message = page_content;
    message.replace("%HOSTNAME%", host_name);
    message.replace("%TEMPERATURE%", GetTemperatureStr());
    message.replace("%HUMIDITY%", GetHumidityStr());
    
    request->send_P(200, "text/html", page_content );*/
    
    //request->send(200, "text/plain", "This is the main server page\n\nNow just testing");   
}

String ESPThermWebServer::MainPageProcessor(const String& var)
{
    if(var == "HOSTNAME"){
      return Config().HostName();
    }
    if(var == "DATE_TIME"){
      return TimeObj().TimeToStringLong(TimeObj().EpochTime());
    }
    /*if(var == "TEMPERATURE")
    if(var == "TEMPERATURE_MIN")
    if(var == "TEMPERATURE_MIN_TS")
    if(var == "TEMPERATURE_MAX")
    if(var == "TEMPERATURE_MAX_TS")
    if(var == "HUMIDITY")
    if(var == "HUMIDITY_MIN")
    if(var == "HUMIDITY_MIN_TS")
    if(var == "HUMIDITY_MAX")
    if(var == "HUMIDITY_MAX_TS")*/
    String err = "Unknown RPC: ";
    err += var;
    return err;
}

void ESPThermWebServer::on_temperature(AsyncWebServerRequest *request)
{
    printlnD("/temperature");
    String str(TemperatureSensor().Temperature());
    request->send(200, "text/plain", str.c_str());
}

void ESPThermWebServer::on_humidity(AsyncWebServerRequest *request)
{
    printlnD("/humidity");
    String str(TemperatureSensor().Humidity());
    request->send(200, "text/plain", str.c_str());
}



  