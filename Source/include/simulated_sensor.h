#ifndef __simulated_sensor_H_
#define __simulated_sensor_H_

#include <ESP8266TrueRandom.h>
#include "sensor.h"

class SimulatedSensor : public Sensor
{
public:
    SimulatedSensor(ESPThermTimeDate& timeDateObj, bool useRandom = true):
        Sensor(timeDateObj),
        m_ESPtimeDateObj(timeDateObj),
        m_Temper (23),
        m_Humid(50),
        m_stamp(0),
        m_UseRandom(useRandom)
         {}
protected:
    bool Random() const {return m_UseRandom;}
    //Read current temperature from sensor 
    virtual float GetCurrentTemperatureFromSensor() override;
    //Read current humidity from sensor
    virtual float GetCurrentHumidityFromSensor() override;   

    ESPThermTimeDate& TimeObj(){ return m_ESPtimeDateObj;}

    bool DoUpdate();

    ESPThermTimeDate& m_ESPtimeDateObj;
    float m_Temper;
    float m_Humid;
    unsigned long m_stamp; 
    bool m_UseRandom;

    

    
};

#endif
