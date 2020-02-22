
#ifndef __htu21_sensor_H_
#define __htu21_sensor_H_

#include <Arduino.h>

#include <Wire.h>
#include "SparkFunHTU21D.h"

#include "sensor.h"


class HTU21Sensor : public Sensor
{
public:
    HTU21Sensor(ESPThermTimeDate& timeDateObj, bool useCelsius = true):
        Sensor(timeDateObj, useCelsius) {}

    void Setup();
protected:

    //Read current temperature from sensor 
    virtual float GetCurrentTemperatureFromSensor() override;
    //Read current humidity from sensor
    virtual float GetCurrentHumidityFromSensor() override;

    HTU21D &HTUSensor() {return m_HTU21Sensor;}
 
    HTU21D m_HTU21Sensor;
    TwoWire m_Wire;
};

#endif