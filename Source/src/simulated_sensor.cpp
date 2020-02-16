#include "simulated_sensor.h"
#include "esp_therm_time_date.h"

bool SimulatedSensor::DoUpdate()
{
    unsigned long now = TimeObj().EpochTime();
    if(!m_stamp){
        m_stamp =now;
        return false;
    }else{
        if((now-m_stamp)>10){
            m_stamp =now;
            return true;
        }
    }
    return false;
}

float SimulatedSensor::GetCurrentTemperatureFromSensor()
{
    if(DoUpdate()){
        if(Random()){
           return ESP8266TrueRandom.random(20,40);     
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
    if(DoUpdate()){
        if(Random()){
           return ESP8266TrueRandom.random(40,90);     
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
