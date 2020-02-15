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