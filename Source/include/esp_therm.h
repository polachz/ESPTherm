#ifndef __esp_therm_class_H_
#define __esp_therm_class_H_

#include <WiFiUdp.h>
#include <NTPClient.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#else
#include <WiFi.h>
#endif

#include "definitions.h"
#include "esp_therm_web_server.h"
#include "sensor.h"

class ESPThermTimeDate;

class ESPTherm
{

public:
    ESPTherm(Sensor& temperatureSensor, ESPThermTimeDate& timeDateObj, int, uint16_t webServerPort = 80):
    m_WebServer(temperatureSensor, webServerPort),
    m_ESPtimeDateObj(timeDateObj)
    {}

    void Setup();
    void LoopOperations();

    ESPThermWebServer &WebServer() {return m_WebServer;}
    const ESPThermWebServer &WebServer() const {return m_WebServer;}
protected:
void configModeCallback (AsyncWiFiManager *myWiFiManager) ;
void saveConfigCallback ();

ESPThermWebServer m_WebServer;

ESPThermTimeDate& m_ESPtimeDateObj;

};

#endif
