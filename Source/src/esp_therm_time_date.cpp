#include "esp_therm_time_date.h"
#include <ctime>

void ESPThermTimeDate::Setup()
{
    m_NTPClient.begin();
    m_NTPClient.forceUpdate();
}
void ESPThermTimeDate::LoopOperations()
{
    m_NTPClient.update();
}

String ESPThermTimeDate::TimeToString(unsigned long timestamp, const ESPThermTimeDateFormat tf)
{
    
    std::time_t epochTime = static_cast<std::time_t>(timestamp);
    std::tm t = *std::gmtime(&epochTime);
    char buff[200];
    switch(tf){
        case ESPThermTimeDateFormat::tdfCZ:
            snprintf (buff, sizeof(buff),
                     "%d.%d. %d %d:%02d",
                     t.tm_mday,t.tm_mon,t.tm_year,
                     t.tm_hour,t.tm_min);
        break;
        case ESPThermTimeDateFormat::tdfUS:
        snprintf (buff, sizeof(buff),
                     "%d/%d/%d %d:%02d",
                     t.tm_mon,t.tm_mday,t.tm_year,
                     t.tm_hour,t.tm_min);
        break;
        default:
            return String("Invalid Time Fmt");
    }
    return String(buff);
}

 String ESPThermTimeDate::TimeToStringLong(unsigned long timestamp, const ESPThermTimeDateFormat tf)
 {
     std::time_t epochTime = static_cast<std::time_t>(timestamp);
    std::tm t = *std::gmtime(&epochTime);
    char buff[200];
    switch(tf){
        case ESPThermTimeDateFormat::tdfCZ:
            snprintf (buff, sizeof(buff),
                     "%d.%d. %d %d:%02d:%02d",
                     t.tm_mday,t.tm_mon+1,t.tm_year+1900,
                     t.tm_hour,t.tm_min,t.tm_sec);
        break;
        case ESPThermTimeDateFormat::tdfUS:
        snprintf (buff, sizeof(buff),
                     "%d/%d/%d %d:%02d:%02d",
                     t.tm_mon+1,t.tm_mday,t.tm_year+1900,
                     t.tm_hour,t.tm_min,t.tm_sec);
        break;
        default:
            return String("Invalid Time Fmt");
    }
    return String(buff);
 }