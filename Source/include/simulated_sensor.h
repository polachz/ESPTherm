#ifndef __simulated_sensor_H_
#define __simulated_sensor_H_

#include "sensor.h"

class SimulatedSensor : public Sensor
{
public:
    SimulatedSensor(ESPThermTimeDate& timeDateObj, bool useRandom = true );
        
protected:
    bool Random() const {return m_UseRandom;}
    //Read current temperature from sensor 
    virtual float GetCurrentTemperatureFromSensor() override;
    //Read current humidity from sensor
    virtual float GetCurrentHumidityFromSensor() override;   

    ESPThermTimeDate& TimeObj(){ return m_ESPtimeDateObj;}

    bool DoUpdate(bool temperature);

    ESPThermTimeDate& m_ESPtimeDateObj;
    float m_Temper;
    float m_Humid;
    unsigned long m_stampTemper; 
    unsigned long m_stampHumid; 
    bool m_UseRandom;

    

    
};

#endif
