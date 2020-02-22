#include <Arduino.h>
#include "definitions.h"
#include "debug.h"

#include <ESPAsyncWiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#include "esp_therm_wifi_manager.h"
#include "esp_therm_time_date.h"
#include "sensor.h"
#include "esp_therm.h"



void ESPTherm::Setup()
{
  if(!Config().Setup()){
    printlnE("Config Setup handlin problem!!!!"); 
    SignalHardError();
    return;
  }
  ConfigWiFiConnection();
  if(Config().IsSaveConfigRequested()){
    if(!Config().SaveToFS()){
      printlnE("Unable to save confgig to FS !!!"); 
      //but we can cvontinue
    }
  }
  TimeObj().Setup();
  WebServer().Setup();

  //Get first measurement
  SensorObj().UpdateCachedValues();

}


void ESPTherm::LoopOperations()
{
    TimeObj().LoopOperations();
    //Now my operations
    //update temperature and humidity each 60 seconds
    if(TimeObj().LoopIntervalInSecondsReached(60)){
        SensorObj().UpdateCachedValues();
    }
}

void ESPTherm::ConfigWiFiConnection()
{
  EspThermWiFiManager wifiManager(Config(),WebServer());
  wifiManager.DoConfig();
}

void ESPTherm::SignalHardError()
{
    printlnE("Hard Error Occurs!"); 
    delay(1000);
    printlnE("HARD Error Occurs!"); 
    delay(1000);
    printlnE("HARD ERROR Occurs!"); 
    delay(2000);
    printlnE("Going to reboot sytem in 1 sec...."); 
    ESP.restart();
}
