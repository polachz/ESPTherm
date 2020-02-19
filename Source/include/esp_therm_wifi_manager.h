#ifndef __esp_therm_time_manager_H_
#define __esp_therm_wifi_manager_H_

#include "esp_therm_config.h"

class ESPThermWebServer;
class AsyncWiFiManager;

class EspThermWiFiManager
{
public:
    EspThermWiFiManager(EspThermConfig& espThermConfig, ESPThermWebServer& espWebServer);

    bool DoConfig();
protected:

EspThermConfig& Config() {return m_ESPThermConfig; }
ESPThermWebServer* WebServerPtr() {return &m_ESPWebServer;}

static void SaveConfigCallback();
static void ConfigModeCallback(AsyncWiFiManager *myWiFiManager);

EspThermConfig& m_ESPThermConfig;
ESPThermWebServer& m_ESPWebServer;
};

#endif