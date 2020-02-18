#include <Arduino.h>
#include "definitions.h"
#include "debug.h"

#include <ESPAsyncWiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#include "esp_therm.h"



void ESPTherm::Setup()
{
  WebServer().Setup();
}


void ESPTherm::LoopOperations()
{

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
    //ESP.restart();
}
