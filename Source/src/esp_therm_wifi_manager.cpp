#include <Arduino.h>
#include "debug.h"
#include <ESPAsyncWiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#include "esp_therm_config.h"
#include "esp_therm_web_server.h"
#include "esp_therm_wifi_manager.h"

EspThermConfig* pConfig =0;


//gets called when WiFiManager enters configuration mode
void EspThermWiFiManager::ConfigModeCallback (AsyncWiFiManager *myWiFiManager) {
  printlnI("Entered AP config mode.");
  printI("SSID: ");
  printlnI(myWiFiManager->getConfigPortalSSID());
  printI("IP: ");
  printlnI(WiFi.softAPIP());
}

//callback notifying us of the need to save config
void EspThermWiFiManager::SaveConfigCallback() {
  printlnD("Should save config");
  if(pConfig){
    pConfig->SetSaveConfigRequest();
  }
}

EspThermWiFiManager::EspThermWiFiManager(EspThermConfig& espThermConfig, ESPThermWebServer& espWebServer):
    m_ESPThermConfig(espThermConfig),
    m_ESPWebServer(espWebServer)
{
     pConfig = &espThermConfig;
}

bool EspThermWiFiManager::DoConfig()
{
    printlnD("wifi manger operations...");
    DNSServer dns;
    AsyncWiFiManager wifiManager(WebServerPtr(),&dns);
    //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
    wifiManager.setAPCallback(ConfigModeCallback);
    //set config save notify callback
    wifiManager.setSaveConfigCallback(SaveConfigCallback);

    AsyncWiFiManagerParameter host_title("<p><b>Host Name:</b></p>");
    wifiManager.addParameter(&host_title);
    AsyncWiFiManagerParameter custom_host_name("HostName", DEFAULT_HOSTNAME, Config().HostName(), 32);
    wifiManager.addParameter(&custom_host_name);
    WiFi.macAddress();
    
    AsyncWiFiManagerParameter mqtt_title("<p><b>MQTT Parameters:</b></p>");
    AsyncWiFiManagerParameter custom_mqtt_host("host", "MQTT hostname", Config().MQTTHost(), 64);
    AsyncWiFiManagerParameter custom_mqtt_port("port", "MQTT port", Config().MQTTPort(), 6);
    AsyncWiFiManagerParameter custom_mqtt_user("user", "MQTT user", Config().MQTTUser(), 32, " maxlength=31");
    AsyncWiFiManagerParameter custom_mqtt_pass("pass", "MQTT pass", Config().MQTTPass(), 32, " maxlength=31 type='password'");
    if(Config().IsMQTTEnabled()){
        wifiManager.addParameter(&mqtt_title);
        wifiManager.addParameter(&custom_mqtt_host);
        wifiManager.addParameter(&custom_mqtt_port);
        wifiManager.addParameter(&custom_mqtt_user);
        wifiManager.addParameter(&custom_mqtt_pass);
    }
String mac_message = "<p>Mac address: ";
mac_message += WiFi.macAddress();
mac_message += "</p>";
AsyncWiFiManagerParameter mac_info(mac_message.c_str());
wifiManager.addParameter(&mac_info);

WiFi.setSleepMode(WIFI_NONE_SLEEP);
  
  // Uncomment if you want to restart ESP8266 if it cannot connect to WiFi.
  // Value in brackets is in seconds that WiFiManger waits until restart
  #ifdef WIFIMGR_PORTAL_TIMEOUT
  wifiManager.setConfigPortalTimeout(WIFIMGR_PORTAL_TIMEOUT);
  #endif

  // Uncomment if you want to set static IP 
  // Order is: IP, Gateway and Subnet 
  #ifdef WIFIMGR_SET_MANUAL_IP
  wifiManager.setSTAStaticIPConfig(IPAddress(_ip[0], _ip[1], _ip[2], _ip[3]), IPAddress(_gw[0], _gw[1], _gw[2], _gw[3]), IPAddress(_sn[0], _sn[1], _sn[2], _sn[3]));
  #endif

    //fetches ssid and pass and tries to connect
    //if it does not connect it starts an access point with the specified name
    //here  "AutoConnectAP"
    //and goes into a blocking loop awaiting configuration
    if (!wifiManager.autoConnect(DEFAULT_HOSTNAME)) {
        printlnE("failed to connect and hit timeout");
        //reset and try again, or maybe put it to deep sleep
        ESP.reset();  //Will be removed when upgrading to standalone offline McLightingUI version
        delay(1000);  //Will be removed when upgrading to standalone offline McLightingUI version
        return false;
    }else{
        printlnI("connected...yeey :)");
    }
    //read updated parameters
    Config().SetHostName(custom_host_name.getValue());
    if(Config().IsMQTTEnabled()){
        Config().SetMQTTHost(custom_mqtt_host.getValue());
        Config().SetMQTTPort(custom_mqtt_port.getValue());
        Config().SetMQTTUser(custom_mqtt_user.getValue());
        Config().SetMQTTPass(custom_mqtt_pass.getValue());
    }      
    printI("IP address:\t");
    printlnI(WiFi.localIP());

    pConfig=0;
    return true;
}

void EspThermWiFiManager::ResetWiFiSettings()
{
  printlnI("The ESPTherm resetting wlan...");
  WiFi.disconnect(true);
  printlnI("The ESPTherm will be rebooted in 2 seconds...");
  delay(2000);
  ESP.restart();

}

void EspThermWiFiManager::RunConfigPortal()
{
  printlnI("The ESPTherm running WiFi config portal...");
  DNSServer dns;
  AsyncWiFiManager wifiManager(WebServerPtr(),&dns);
  wifiManager.startConfigPortal(Config().HostName());
}