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
        m_ESPtimeDateObj(timeDateObj),
        m_FactoryResetRequired(false),
        m_WlanResetRequired(false),
        m_RunAPConfigRequired(false),
        m_WebPageUpdateRequestReceived(false) {}

    void Setup();

    bool IsFactoryResetRequired();
    bool IsWlanResetRequired();
    bool IsRunAPConfigRequired();
    bool IsWebPageUpdateRequestReceived();
    
protected:

    EspThermConfig &Config() {return m_Config;}
    const EspThermConfig &Config() const {return m_Config;}

    ESPThermTimeDate& TimeObj(){ return m_ESPtimeDateObj;}
    const ESPThermTimeDate& TimeObj()const { return m_ESPtimeDateObj;}

    Sensor& SensorObj(){ return m_Sensor;}
    const Sensor& SensorObj()const { return m_Sensor;}

    String MainPageProcessor(const String& var);
    //Web handlers:
    void on_not_found(AsyncWebServerRequest *request);
    void on_root(AsyncWebServerRequest *request);
    void on_temperature(AsyncWebServerRequest *request);
    void on_humidity(AsyncWebServerRequest *request);
    void on_get_web_values(AsyncWebServerRequest *request);
    void on_factory_reset(AsyncWebServerRequest *request);
    void on_reset_wlan(AsyncWebServerRequest *request);
    void on_start_config_ap(AsyncWebServerRequest *request);

    static String TemperatureToString(float temperature);

    static String HumidityToString( float humidity);

    Sensor& m_Sensor;

    EspThermConfig &m_Config;
    ESPThermTimeDate& m_ESPtimeDateObj;

    bool m_FactoryResetRequired;
    bool m_WlanResetRequired;
    bool m_RunAPConfigRequired;

    bool m_WebPageUpdateRequestReceived;

};
#endif