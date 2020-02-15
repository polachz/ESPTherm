
#ifndef __htu21_sensor_H_
#define __htu21_sensor_H_

#include <Arduino.h>

#include <Wire.h>
#include "SparkFunHTU21D.h"

#include "sensor.h"

class HTU21Sensor : public Sensor
{
public:
    HTU21Sensor(ESPThermTimeDate& timeDate):
        Sensor(timeDate) {}

    void Setup();
protected:

    //Read current temperature from sensor 
    virtual float GetCurrentTemperatureFromSensor() override;
    //Read current humidity from sensor
    virtual float GetCurrentHumidityFromSensor() override;

    HTU21D &HTUSensor() {return m_Sensor;}
 
    HTU21D m_Sensor;
    TwoWire m_Wire;
};

#endif