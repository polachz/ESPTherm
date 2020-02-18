#include <stdint.h>
#include "definitions.h"
#include "debug.h"
#include <ArduinoJson.h>
#include <FS.h>
#include "esp_therm_config.h"


EspThermConfig::EspThermConfig():m_Mounted(false)
{
  memset(m_HostName,0,sizeof(m_HostName));
  memset(m_MQTTHost,0,sizeof(m_MQTTHost));
  memset(m_MQTTPort,0,sizeof(m_MQTTPort));
  memset(m_MQTTUser,0,sizeof(m_MQTTUser));
  memset(m_MQTTPass,0,sizeof(m_MQTTPass));
}

bool EspThermConfig::Setup()
{
  bool loadDefaults = false;
  if(!MountFS()){
    loadDefaults = true;
  }else{
    if(!LoadFromFS()){
      loadDefaults = true;
    }
  }
  if(loadDefaults){
    FillByDefaults();
  }
  return !loadDefaults;
}

bool EspThermConfig::MountFS()
{
  if(SPIFFS.begin()){
        printlnI("FS has been mounted sucessfully")
        if (!_debugSilence && _debugLevel >= DEBUG_LEVEL_VERBOSE){
            Dir dir = SPIFFS.openDir("/");
            while (dir.next()) {
              String fileName = dir.fileName();
              size_t fileSize = dir.fileSize();
              debugV("FS File: %s, size: %s\n", fileName.c_str(), FormatBytes(fileSize).c_str());
            }

            FSInfo fs_info;
            SPIFFS.info(fs_info);
            debugV("FS Usage: %d/%d bytes\n\n", fs_info.usedBytes, fs_info.totalBytes);
        }
        m_Mounted = true;
  }else{
     printlnE("Failed to mount FS"); 
  }
  return m_Mounted;
}
bool EspThermConfig::LoadFromFS()
{
  if(!FSMounted()){ 
    return false;
  }
  //read configuration from FS JSON
  if (SPIFFS.exists("/config.json")) {
    //file exists, reading and loading
    printlnD("Reading config file... ");
    File configFile = SPIFFS.open("/config.json", "r");
    if (configFile) {
      printlnD("Config File opened");
      size_t size = configFile.size();
      std::unique_ptr<char[]> buf(new char[size]);
      configFile.readBytes(buf.get(), size);
      DynamicJsonDocument json(JSON_OBJECT_SIZE(6)+300);
      DeserializationError error = deserializeJson(json, buf.get());
      if (!error) {
        printlnI("Config parsed successfully.");
        if (!_debugSilence && _debugLevel >= DEBUG_LEVEL_VERBOSE){
          //JsonObject jsonO = jsonBuffer.as<JsonObject>();
          String sss;
          serializeJson(json, sss);
          printlnD(sss);
        }
        //The | operator is overoladed at the JSONVariant Class and allows to set here default
        strlcpy(m_HostName, json["host_name"] | DEFAULT_HOSTNAME, sizeof(m_HostName));
        //to be sure, write zero on the end
        m_HostName[sizeof(m_HostName)-1]=0;
        strlcpy(m_MQTTHost, json["mqtt_host"] | DEFAULT_MQTT_HOST, sizeof(m_MQTTHost));
        m_MQTTHost[sizeof(m_MQTTHost)-1]=0;
        strlcpy(m_MQTTPort, json["mqtt_port"] | DEFAULT_MQTT_PORT, sizeof(m_MQTTPort));
        m_MQTTPort[sizeof(m_MQTTPort)-1]=0;
        strlcpy(m_MQTTUser, json["mqtt_user"] | DEFAULT_MQTT_USER, sizeof(m_MQTTUser));
        m_MQTTUser[sizeof(m_MQTTUser)-1]=0;
        strlcpy(m_MQTTPass, json["mqtt_pass"] | DEFAULT_MQTT_PASS, sizeof(m_MQTTPass));
        m_MQTTPass[sizeof(m_MQTTPass)-1]=0;

        return true;
      } else {
        debugE("Failed to parse config: %s \n",error.c_str());
      }
    } else {
      printlnE("Failed to open config file");
    }
  } else {
    printlnD("Coudnt find config file");
  }
  //end read
  return false;
}
void EspThermConfig::FillByDefaults()
{
  strlcpy(m_HostName, DEFAULT_HOSTNAME, sizeof(m_HostName));
  //to be sure, write zero on the end
  m_HostName[sizeof(m_HostName)-1]=0;
  strlcpy(m_MQTTHost, DEFAULT_MQTT_HOST, sizeof(m_MQTTHost));
  m_MQTTHost[sizeof(m_MQTTHost)-1]=0;
  strlcpy(m_MQTTPort, DEFAULT_MQTT_PORT, sizeof(m_MQTTPort));
  m_MQTTPort[sizeof(m_MQTTPort)-1]=0;
  strlcpy(m_MQTTUser, DEFAULT_MQTT_USER, sizeof(m_MQTTUser));
  m_MQTTUser[sizeof(m_MQTTUser)-1]=0;
  strlcpy(m_MQTTPass, DEFAULT_MQTT_PASS, sizeof(m_MQTTPass));
  m_MQTTPass[sizeof(m_MQTTPass)-1]=0;

}
bool EspThermConfig::SaveToFS()
{
  DynamicJsonDocument json(JSON_OBJECT_SIZE(6)+300);
   json["host_name"] = HostName();
   json["mqtt_host"] = MQTTHost();
   json["mqtt_port"] = MQTTPort();
   json["mqtt_user"] = MQTTUser();
   json["mqtt_pass"] = MQTTPass();

  String sss;   
  serializeJson(json, sss);
  if (!_debugSilence && _debugLevel >= DEBUG_LEVEL_VERBOSE){
    printlnD("Config content:")
    printlnD(sss);
  }
  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile) { 
    printlnE("Failed to open config file for writing");
    return false;
  }
  int wb = configFile.print(sss);
  configFile.close();
  if(wb<=0){
    printlnE("Failed to write config to file");
    return false;
    
  }
  return true;
}

String EspThermConfig::FormatBytes(size_t bytes)
{
  if (bytes < 1024) {
		return String(bytes) + "B";
	} else if (bytes < (1024 * 1024)) {
		return String(bytes / 1024.0) + "KB";
	} else if (bytes < (1024 * 1024 * 1024)) {
		return String(bytes / 1024.0 / 1024.0) + "MB";
	} else {
		return String(bytes / 1024.0 / 1024.0 / 1024.0) + "GB";
	}
}
 