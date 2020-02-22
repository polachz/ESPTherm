#include "simulated_sensor.h"
#include "esp_therm_time_date.h"


SimulatedSensor::SimulatedSensor(ESPThermTimeDate& timeDateObj, bool useRandom ):
        Sensor(timeDateObj),
        m_ESPtimeDateObj(timeDateObj),
        m_Temper (23),
        m_Humid(50),
        m_stampTemper(0),
        m_stampHumid(0),
        m_UseRandom(useRandom)
         { randomSeed(timeDateObj.EpochTime());
         }

bool SimulatedSensor::DoUpdate(bool temperature)
{
    unsigned long& stamp=temperature? m_stampTemper : m_stampHumid;
    unsigned long now = TimeObj().EpochTime();
    if(!stamp){
        stamp =now;
        return false;
    }else{
        if((now- stamp)>10){
            stamp =now;
            return true;
        }
    }
    return false;
}

float SimulatedSensor::GetCurrentTemperatureFromSensor()
{
    if(DoUpdate(true)){
        if(Random()){
           return ((float)random(200,400))/10;     
        }else{
            if(m_Temper > 38){
                m_Temper = 20;
            }else{
                m_Temper=m_Temper+2;
            }
        }
    }
    return m_Temper+0.3;
}
float SimulatedSensor::GetCurrentHumidityFromSensor()
{
    if(DoUpdate(false)){
        if(Random()){
           return random(40,90);     
        }else{
            if(m_Humid > 90){
                m_Humid=40;
            }else{
                m_Humid+=10;
            }
        }
    }
    return m_Humid;
}
