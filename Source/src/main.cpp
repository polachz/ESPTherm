#include <Arduino.h>
#include "debug.h"

#if defined(ESP8266)
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#else
#include <WiFi.h>
#endif

#include <ESPAsyncWebServer.h>     //Local WebServer used to serve the configuration portal
#include <ESPAsyncWiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#include "definitions.h"
#include "wifi_manager.h"

#include "config.h"
#include "common_funcs.h"

#include "web_server.h"

AsyncWebServer server(80);

bool doFactoryReset=false;
bool doResetWlan=false;
bool runConfig_ap=false;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  debugSetLevel(DEBUG_INITIAL_LEVEL);
  
  wifi_manager_operations();
  
  web_server_register_handlers(server);
  //fire the server
  server.begin();
}

void loop() {
  debugHandle();
  //delay(1000);
  //debugI("Hostname: %s",host_name);
  delay(1000);
  if(doFactoryReset){
    doFactoryReset=false;
    printlnI("The ESPTherm will be completely erased!");
    doResetWlan = true;
  }
  if(doResetWlan){
    doResetWlan=false;
    printlnI("The ESPTherm resetting wlan...");
    WiFi.disconnect(true);
    printlnI("The ESPTherm will be rebooted in 2 seconds...");
    delay(2000);
    ESP.restart();
  }
  if(runConfig_ap){
    runConfig_ap=false;
    printlnI("The ESPTherm running WiFi config portal...");
    DNSServer dns;
    AsyncWiFiManager wm(&server,&dns);
    wm.startConfigPortal(HOSTNAME);
  }
}