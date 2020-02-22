#include "debug.h"
#include "sensor.h"

Sensor::Sensor(ESPThermTimeDate &timeDateObj,bool useCelsius ):
    m_TemperatureMin(timeDateObj),
    m_TemperatureMax(timeDateObj),
    m_HumidityMin(timeDateObj),
    m_HumidityMax(timeDateObj),
    m_Celsius(useCelsius)
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

float Sensor::CelsiusToFarenheit(float celsius)
{
    return celsius * 9/5 + 32;
}

void Sensor::UpdateCachedValues() {
        printlnI("Refreshing Cached Temp and Humidity Values");
        Temperature();
        Humidity();
    }