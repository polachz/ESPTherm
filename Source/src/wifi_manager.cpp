
#include <Arduino.h>
#include "definitions.h"
#include "debug.h"

#if defined(ESP8266)
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#else
#include <WiFi.h>
#endif
#include <ESPAsyncWiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#include "common_funcs.h"
#include "esp_therm_web_server.h"
#include "config.h"

//80:7D:3A:33:96:A6
//172.17.17.238


bool shouldSaveConfig = false;  // For WiFiManger custom config


//gets called when WiFiManager enters configuration mode
void configModeCallback (AsyncWiFiManager *myWiFiManager) {
  printlnI("Entered AP config mode.");
  printI("SSID: ");
  printlnI(myWiFiManager->getConfigPortalSSID());
  printI("IP: ");
  printlnI(WiFi.softAPIP());
}


//callback notifying us of the need to save config
void saveConfigCallback () {
  printlnD("Should save config");
  shouldSaveConfig = true;
}

void wifi_manager_operations(ESPThermWebServer& estWebServer)
{
  printlnD("wifi manger operations...");
  DNSServer dns;
  AsyncWiFiManager wifiManager(&estWebServer,&dns);
    //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wifiManager.setAPCallback(configModeCallback);

  //set config save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);
  AsyncWiFiManagerParameter host_title("<p><b>Host Name:</b></p>");
  wifiManager.addParameter(&host_title);
  AsyncWiFiManagerParameter custom_host_name("name", HOSTNAME, host_name, 32);
  wifiManager.addParameter(&custom_host_name);
  WiFi.macAddress();
#if defined(ENABLE_AMQTT)
AsyncWiFiManagerParameter mqtt_title("<p><b>MQTT Parameters:</b></p>");
  wifiManager.addParameter(&mqtt_title);
  AsyncWiFiManagerParameter custom_mqtt_host("host", "MQTT hostname", mqtt_host, 64);
  AsyncWiFiManagerParameter custom_mqtt_port("port", "MQTT port", mqtt_port, 6);
  AsyncWiFiManagerParameter custom_mqtt_user("user", "MQTT user", mqtt_user, 32, " maxlength=31");
  AsyncWiFiManagerParameter custom_mqtt_pass("pass", "MQTT pass", mqtt_pass, 32, " maxlength=31 type='password'");
  wifiManager.addParameter(&custom_mqtt_host);
  wifiManager.addParameter(&custom_mqtt_port);
  wifiManager.addParameter(&custom_mqtt_user);
  wifiManager.addParameter(&custom_mqtt_pass);
#endif
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
    if (!wifiManager.autoConnect(HOSTNAME)) {
        printlnE("failed to connect and hit timeout");
        //reset and try again, or maybe put it to deep sleep
        ESP.reset();  //Will be removed when upgrading to standalone offline McLightingUI version
        delay(1000);  //Will be removed when upgrading to standalone offline McLightingUI version
    }else{
        printlnI("connected...yeey :)");
    }
    //read updated parameters
    
      
 /*     
#if defined(ENABLE_AMQTT)
      strcpy(mqtt_host, custom_mqtt_host.getValue());
      DBG_OUTPUT_PORT.println("C1");
      strcpy(mqtt_port, custom_mqtt_port.getValue());
      DBG_OUTPUT_PORT.println("C2");
      strcpy(mqtt_user, custom_mqtt_user.getValue());
      DBG_OUTPUT_PORT.println("C3");
      strcpy(mqtt_pass, custom_mqtt_pass.getValue());
      DBG_OUTPUT_PORT.println("C4");
#endif
        
      strcpy(host_name, custom_host_name.getValue());  
      DBG_OUTPUT_PORT.println("C5");
*/
        printI("IP address:\t");
        printlnI(WiFi.localIP());
}
