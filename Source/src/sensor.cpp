#include "sensor.h"

Sensor::Sensor(ESPThermTimeDate &timeDateObj ):
    m_TemperatureMin(timeDateObj),
    m_TemperatureMax(timeDateObj),
    m_HumidityMin(timeDateObj),
    m_HumidityMax(timeDateObj)
{}

float Sensor::Temperature()
{
    float temperature = GetCurrentTemperatureFromSensor();
    m_TemperatureMin.UpdateValue(temperature);
    m_TemperatureMax.UpdateValue(temperature);
    return temperature;
}

float Sensor::Humidity()
{
    float humidity = GetCurrentHumidityFromSensor();  
    m_HumidityMin.UpdateValue(humidity);
    m_HumidityMax.UpdateValue(humidity);  

    return humidity;
}