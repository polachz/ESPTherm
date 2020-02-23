#ifndef __definitions_H_
#define __definitions_H_

#define SDA_PIN 0
#define SCL_PIN 2

//#define BOARD_LED 1    // ESP-12F has the built in LED on GPIO2, see https://github.com/esp8266/Arduino/issues/2192

#define DEFAULT_HOSTNAME "ESPTherm"   // Friendly hostname

#define USE_MQTT false

//If true, measurement values are in degrees of Celsius
//If false, easurement values are in degrees of Farenheit
#define USE_DEGREE_OF_CELSIUS true

//Offset in seconds for the time zone. 
//UTC+1 = 3600
#define NTP_TIME_ZONE_OFFSET 3600
#define NTP_REFRESH_TIME 60000
#define NTP_POOL "europe.pool.ntp.org"

enum class ESPThermTimeDateFormat
{
    tdfCZ,
    tdfUS
};

#define TIME_DATE_FORMAT ESPThermTimeDateFormat::tdfCZ

#define DEFAULT_MQTT_HOST ""
#define DEFAULT_MQTT_PORT ""
#define DEFAULT_MQTT_USER ""
#define DEFAULT_MQTT_PASS ""






#endif