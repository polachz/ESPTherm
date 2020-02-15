#ifndef __esp_therm_web_server_H_
#define __esp_therm_web_server_H_

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>     //Local WebServer used to serve the configuration portal
#include "definitions.h"
#include "sensor.h"

class ESPThermWebServer: public AsyncWebServer
{
public:
    ESPThermWebServer(Sensor& temperatureSensor, uint16_t webServerPort):
        AsyncWebServer(webServerPort),
        m_Sensor(temperatureSensor){}

    void Setup();
protected:

    //Web handlers:
    void on_not_found(AsyncWebServerRequest *request);
    void on_root(AsyncWebServerRequest *request);
    void on_temperature(AsyncWebServerRequest *request);
    void on_humidity(AsyncWebServerRequest *request);

    Sensor& TemperatureSensor() {return m_Sensor;}
    const Sensor& TemperatureSensor()const {return m_Sensor;}

    Sensor& m_Sensor;

};
#endif