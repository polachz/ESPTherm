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
  this->on("/humidity", HTTP_GET,std::bind( &ESPThermWebServer::on_humidity, this, _1 ));
  this->on("/gwv", HTTP_GET,std::bind( &ESPThermWebServer::on_get_web_values, this, _1 ));
  this->on("/factoryReset", HTTP_GET,std::bind( &ESPThermWebServer::on_factory_reset, this, _1 ));
  this->on("/resetWlan", HTTP_GET,std::bind( &ESPThermWebServer::on_reset_wlan, this, _1 ));
  this->on("/startConfigAP", HTTP_GET,std::bind( &ESPThermWebServer::on_start_config_ap, this, _1 ));
    
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
}

String ESPThermWebServer::MainPageProcessor(const String& var)
{
    if(var == "HOSTNAME"){
      return Config().HostName();
    }
    if(var == "DATE_TIME"){
      return TimeObj().TimeToStringLong(TimeObj().EpochTime());
    }
    if(var == "TUNIT"){
      return SensorObj().UseCelsius()?"C":"F";
    }
    if(var == "TEMPERATURE"){
      return TemperatureToString(SensorObj().Temperature());
    }
    if(var == "TEMPERATURE_MIN"){
      return TemperatureToString(SensorObj().TemperatureMin().Value());
    }
    if(var == "TEMPERATURE_MIN_TS"){
      return TimeObj().TimeToString(SensorObj().TemperatureMin().TimeStamp());
    }
    if(var == "TEMPERATURE_MAX"){
      return TemperatureToString(SensorObj().TemperatureMax().Value());
    }
    if(var == "TEMPERATURE_MAX_TS"){
      return TimeObj().TimeToString(SensorObj().TemperatureMax().TimeStamp());
    }
    if(var == "HUMIDITY"){
      return HumidityToString(SensorObj().Humidity());
    }
    if(var == "HUMIDITY_MIN"){
      return HumidityToString(SensorObj().HumidityMin().Value());
    }
    if(var == "HUMIDITY_MIN_TS"){
      return TimeObj().TimeToString(SensorObj().HumidityMin().TimeStamp());
    }
    if(var == "HUMIDITY_MAX"){
        return HumidityToString(SensorObj().HumidityMax().Value());
    }
    if(var == "HUMIDITY_MAX_TS"){
        return TimeObj().TimeToString(SensorObj().HumidityMax().TimeStamp());
    }
    if(var == "PROC"){
        return "%";
    }
    String err = "Unknown RPC: ";
    err += var;
    return err;
}

void ESPThermWebServer::on_temperature(AsyncWebServerRequest *request)
{
    printlnD("/temperature");
    String str = TemperatureToString(SensorObj().Temperature());
    request->send(200, "text/plain", str.c_str());
}

void ESPThermWebServer::on_humidity(AsyncWebServerRequest *request)
{
    printlnD("/humidity");
    String str = HumidityToString(SensorObj().Humidity());
    request->send(200, "text/plain", str.c_str());
}

void ESPThermWebServer::on_get_web_values(AsyncWebServerRequest *request)
{
  String str;
  str = Config().HostName();
  str += ",";
  str += TimeObj().TimeToStringLong(TimeObj().EpochTime());
  str += ",";
  str += TemperatureToString(SensorObj().Temperature());
  str += ",";
  str += TemperatureToString(SensorObj().TemperatureMin().Value());
  str += ",";
  str += TimeObj().TimeToString(SensorObj().TemperatureMin().TimeStamp());
  str += ",";
  str += TemperatureToString(SensorObj().TemperatureMax().Value());
  str += ",";
  str +=  TimeObj().TimeToString(SensorObj().TemperatureMax().TimeStamp());
  str += ",";
  str +=  HumidityToString(SensorObj().Humidity());
  str += ",";
  str +=  HumidityToString(SensorObj().HumidityMin().Value());
  str += ",";
  str +=  TimeObj().TimeToString(SensorObj().HumidityMin().TimeStamp());
  str += ",";
  str +=  HumidityToString(SensorObj().HumidityMax().Value());
  str += ",";
  str +=  TimeObj().TimeToString(SensorObj().HumidityMax().TimeStamp());
  m_WebPageUpdateRequestReceived=true;
  request->send(200, "text/plain", str.c_str());
}

void ESPThermWebServer::on_factory_reset(AsyncWebServerRequest *request)
{
  printlnI("Erase request received...");
  request->send(200, "text/plain", "Erase request received.\nAll configuration data will be lost!!\nThe ESPTherm will be eerased and rebooted in a while...");  
  m_FactoryResetRequired =true;
  printlnD("Reset Request Marked up!");
}

void ESPThermWebServer::on_reset_wlan(AsyncWebServerRequest *request)
{
  printlnI("reset_wlan request received...");
  AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "Resetting WLAN and restarting..." );
  response->addHeader("Access-Control-Allow-Origin", "*");
  request->send(response);
  m_WlanResetRequired=true;
}

void ESPThermWebServer::on_start_config_ap(AsyncWebServerRequest *request)
{
  printlnI("configAP request received...");
  AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "Starting config AP ..." );
  response->addHeader("Access-Control-Allow-Origin", "*");
  request->send(response);
  m_RunAPConfigRequired=true;
}


String ESPThermWebServer::TemperatureToString(float temperature)
{
  String s(temperature,1);
  return s;
}

String ESPThermWebServer::HumidityToString( float humidity)
{
  String s(humidity,0);
  return s;
}

bool ESPThermWebServer::IsFactoryResetRequired()
{
  if(m_FactoryResetRequired){
    m_FactoryResetRequired = false;
    return true;
  }
  return false;
}
bool ESPThermWebServer::IsWlanResetRequired()
{
  if(m_WlanResetRequired){
    m_WlanResetRequired = false;
    return true;
  }
  return false;
}
bool ESPThermWebServer::IsRunAPConfigRequired()
{
  if(m_RunAPConfigRequired){
    m_RunAPConfigRequired = false;
    return true;
  }
  return false;
}
bool ESPThermWebServer::IsWebPageUpdateRequestReceived()
{
  if(m_WebPageUpdateRequestReceived){
      m_WebPageUpdateRequestReceived =false;
      return true;
  }
  return false;
}



  