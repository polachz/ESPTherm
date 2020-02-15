#ifndef __esp_therm_time_date_H_
#define __esp_therm_time_date_H_

#include <WiFiUdp.h>
#include <NTPClient.h>

#include "definitions.h"

class ESPThermTimeDate
{
public:

    ESPThermTimeDate(ESPThermTimeDateFormat tdFormat, const char* poolServerName, int timeOffset, int updateInterval):
        m_TDFormat(tdFormat),
        m_NTPClient(m_UDP,poolServerName,timeOffset,updateInterval)
        {}
    
    unsigned long EpochTime() {return m_NTPClient.getEpochTime();}

    void Setup();
    void LoopOperations();
    static String TimeToString(unsigned long timestamp, const ESPThermTimeDateFormat tf);
    static String TimeToStringLong(unsigned long timestamp, const ESPThermTimeDateFormat tf);
protected:
    const ESPThermTimeDateFormat m_TDFormat;

    WiFiUDP m_UDP;
    NTPClient m_NTPClient;

};

#endif
