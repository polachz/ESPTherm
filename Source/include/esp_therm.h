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
#include "esp_therm_config.h"
#include "sensor.h"

class ESPThermTimeDate;

class ESPTherm
{

public:
    ESPTherm(bool useMQTT, Sensor& temperatureSensor, ESPThermTimeDate& timeDateObj, int, uint16_t webServerPort = 80):
    m_WebServer(m_Config, temperatureSensor, timeDateObj, webServerPort),
    m_Config(useMQTT),
    m_ESPtimeDateObj(timeDateObj)
    
    {}

    void Setup();
    void LoopOperations();

    ESPThermWebServer &WebServer() {return m_WebServer;}
    const ESPThermWebServer &WebServer() const {return m_WebServer;}

    EspThermConfig &Config() {return m_Config;}
    const EspThermConfig &Config() const {return m_Config;}

    
    static void SignalHardError();
protected:

    void ConfigWiFiConnection();

    ESPThermTimeDate& TDObj(){return m_ESPtimeDateObj;}

    ESPThermWebServer m_WebServer;
    EspThermConfig m_Config;

    ESPThermTimeDate& m_ESPtimeDateObj;



};

#endif
