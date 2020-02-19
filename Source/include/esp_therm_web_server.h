#ifndef __esp_therm_web_server_H_
#define __esp_therm_web_server_H_

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>     //Local WebServer used to serve the configuration portal
#include "definitions.h"
#include "sensor.h"

class EspThermConfig;
class ESPThermTimeDate;

class ESPThermWebServer: public AsyncWebServer
{
public:
    ESPThermWebServer(EspThermConfig& espConfig, Sensor& temperatureSensor, ESPThermTimeDate& timeDateObj, uint16_t webServerPort):
        AsyncWebServer(webServerPort),
        m_Sensor(temperatureSensor),
        m_Config(espConfig),
        m_ESPtimeDateObj(timeDateObj) {}

    void Setup();
protected:

    EspThermConfig &Config() {return m_Config;}
    const EspThermConfig &Config() const {return m_Config;}

    ESPThermTimeDate& TimeObj(){ return m_ESPtimeDateObj;}
    const ESPThermTimeDate& TimeObj()const { return m_ESPtimeDateObj;}

    String MainPageProcessor(const String& var);
    //Web handlers:
    void on_not_found(AsyncWebServerRequest *request);
    void on_root(AsyncWebServerRequest *request);
    void on_temperature(AsyncWebServerRequest *request);
    void on_humidity(AsyncWebServerRequest *request);

    Sensor& TemperatureSensor() {return m_Sensor;}
    const Sensor& TemperatureSensor()const {return m_Sensor;}

    Sensor& m_Sensor;
    EspThermConfig &m_Config;
    ESPThermTimeDate& m_ESPtimeDateObj;

};
#endif