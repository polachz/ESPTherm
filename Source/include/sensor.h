#ifndef __sensor_H_
#define __sensor_H_

#include "min_max.h"

class ESPThermTimeDate;;

class Sensor
{
    
protected:
    Sensor(ESPThermTimeDate& timeDateObj, bool useCelsius = true);

public:

    bool UseCelsius()const { return m_Celsius;}
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

    //Used to record min/max values when no web page is shown. Used by loop
    void UpdateValues();

    virtual void Setup() =0;
protected:

    static float CelsiusToFarenheit(float celsius);

    //Must be overriden. Read current temperature from sensor (based on sensor HW type)
    //On error, return value > 900
    virtual float GetCurrentTemperatureFromSensor()=0;
    //Must be overriden. Read current humidity from sensor (based on sensor HW type)
    //On error, return value > 900
    virtual float GetCurrentHumidityFromSensor()=0;

    float m_CachedTemperature;
    float m_CachedHumidity;

    CMinValue m_TemperatureMin;
    CMaxValue m_TemperatureMax;

    CMinValue m_HumidityMin;
    CMaxValue m_HumidityMax;

    bool m_Celsius;
    
};

#endif