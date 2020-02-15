#ifndef __sensor_H_
#define __sensor_H_

#include "min_max.h"

class ESPThermTimeDate;;

class Sensor
{
    
protected:
    Sensor(ESPThermTimeDate& timeDateObj );

public:
    //Read temperature from sensor and returns currently measured value
    float Temperature();
    //Returns minimal temperature value measured since begining of measurements
    const ValueWithTimeStamp& TemperatureMin()const {return m_TemperatureMin.GetValueAndStamp();}
    //Returns maximal temperature value measured since begining of measurements
    const ValueWithTimeStamp& TemperatureMax()const {return m_TemperatureMax.GetValueAndStamp();}


    //Read humidity from sensor and returns currently measured value
    float Humidity();
    //Returns minimal humidity value measured since begining of measurements
    const ValueWithTimeStamp& HumidityMin()const {return m_HumidityMin.GetValueAndStamp();}
    //Returns maximal humidity value measured since begining of measurements
    const ValueWithTimeStamp& HumidityMax()const {return m_HumidityMax.GetValueAndStamp();}

protected:

    //Must be overriden. Read current temperature from sensor (based on sensor HW type)
    virtual float GetCurrentTemperatureFromSensor()=0;
    //Must be overriden. Read current humidity from sensor (based on sensor HW type)
    virtual float GetCurrentHumidityFromSensor()=0;

    CMinValue m_TemperatureMin;
    CMaxValue m_TemperatureMax;

    CMinValue m_HumidityMin;
    CMaxValue m_HumidityMax;
    
};

#endif