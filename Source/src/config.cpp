#include <stdint.h>
#include "definitions.h"
#include "debug.h"
#include <ArduinoJson.h>
#include <FS.h>
#include "common_funcs.h"

char host_name[32] = HOSTNAME;

#if defined(ENABLE_AMQTT)

char mqtt_host[64] = "";
char mqtt_port[6] = "";
char mqtt_user[32] = "";
char mqtt_pass[32] = "";

#endif


void config_storage_setup()
{
    if(SPIFFS.begin()){
        printlnI("FS has been mounted sucessfully")
        if (!_debugSilence && _debugLevel >= DEBUG_LEVEL_VERBOSE){
            Dir dir = SPIFFS.openDir("/");
            while (dir.next()) {
              String fileName = dir.fileName();
              size_t fileSize = dir.fileSize();
              debugV("FS File: %s, size: %s\n", fileName.c_str(), formatBytes(fileSize).c_str());
            }

            FSInfo fs_info;
            SPIFFS.info(fs_info);
            debugV("FS Usage: %d/%d bytes\n\n", fs_info.usedBytes, fs_info.totalBytes);
        }
  }else{
     printlnE("Failed to mount FS"); 
  }
}

bool load_config_from_fs()
{
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
        strlcpy(host_name, json["host_name"] | HOSTNAME, sizeof(host_name));
        host_name[sizeof(host_name)-1]=0;
#if defined(ENABLE_AMQTT)        
        strlcpy(mqtt_host, json["mqtt_host"] | HOSTNAME, sizeof(mqtt_host));
        mqtt_host[sizeof(mqtt_host)-1]=0;
        strlcpy(mqtt_port, json["mqtt_port"] | HOSTNAME, sizeof(mqtt_port));
        mqtt_port[sizeof(mqtt_port)-1]=0;
        strlcpy(mqtt_user, json["mqtt_user"] | HOSTNAME, sizeof(mqtt_user));
        mqtt_user[sizeof(mqtt_user)-1]=0;
        strlcpy(mqtt_pass, json["mqtt_pass"] | HOSTNAME, sizeof(mqtt_pass));
        mqtt_pass[sizeof(mqtt_pass)-1]=0;
#endif
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

bool save_config_to_fs()
{
   DynamicJsonDocument json(JSON_OBJECT_SIZE(6)+300);
   json["host_name"]=host_name;
#if defined(ENABLE_AMQTT) 
   json["mqtt_host"] = mqtt_host;
   json["mqtt_port"] = mqtt_port;
   json["mqtt_user"] = mqtt_user;
   json["mqtt_pass"] = mqtt_pass;
#endif
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
 