#include <Arduino.h>
#include "debug.h"

#include <NTPClient.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#else
#include <WiFi.h>
#endif

#include <ESPAsyncWiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#include "definitions.h"

#include "simulated_sensor.h"
#include "htu21_sensor.h"

#include "esp_therm_time_date.h"
#include "esp_therm.h"

bool doFactoryReset=false;
bool doResetWlan=false;
bool runConfig_ap=false;

ESPThermTimeDate espThermTimeDate(TIME_DATE_FORMAT, NTP_POOL,NTP_TIME_ZONE_OFFSET, NTP_REFRESH_TIME );

/*HTU21Sensor htuSensor(espThermTimeDate);
ESPTherm espTherm(USE_MQTT, htuSensor,espThermTimeDate,80);*/

SimulatedSensor simSensor(espThermTimeDate);
ESPTherm espTherm(USE_MQTT, simSensor,espThermTimeDate,80);

void setup() {
  //Initialize debugging
  Serial.begin(115200);
  debugSetLevel(DEBUG_INITIAL_LEVEL);
  espTherm.Setup();  
}

void loop() {
  debugHandle();
  //delay(1000);
  //debugI("Hostname: %s",host_name);
  espThermTimeDate.LoopOperations();
  espTherm.LoopOperations();
  unsigned long px = espThermTimeDate.EpochTime();
  Serial.println(espThermTimeDate.TimeToString(px,ESPThermTimeDateFormat::tdfCZ).c_str());
  Serial.println(espThermTimeDate.TimeToStringLong(px,ESPThermTimeDateFormat::tdfCZ).c_str());
  Serial.println(espThermTimeDate.TimeToString(px,ESPThermTimeDateFormat::tdfUS).c_str());
  Serial.println(espThermTimeDate.TimeToStringLong(px,ESPThermTimeDateFormat::tdfUS).c_str());
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
    /*DNSServer dns;
    AsyncWiFiManager wm(&server,&dns);
    wm.startConfigPortal(HOSTNAME);*/
  }
}