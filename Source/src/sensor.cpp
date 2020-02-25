#include "debug.h"
#include "sensor.h"

Sensor::Sensor(ESPThermTimeDate &timeDateObj,bool useCelsius ):
    m_CachedTemperature(-100),
    m_CachedHumidity(500),
    m_TemperatureMin(timeDateObj),
    m_TemperatureMax(timeDateObj),
    m_HumidityMin(timeDateObj),
    m_HumidityMax(timeDateObj),
    m_Celsius(useCelsius)
{}

float Sensor::Temperature()
{
    return m_CachedTemperature;
}

float Sensor::Humidity()
{
    return m_CachedHumidity;
}

float Sensor::CelsiusToFarenheit(float celsius)
{
    return celsius * 9/5 + 32;
}

void Sensor::UpdateValues() {
    printlnI("Refreshing Cached Temp and Humidity Values");
    float temperature = GetCurrentTemperatureFromSensor();
    m_CachedTemperature=temperature;
    m_TemperatureMin.UpdateValue(temperature);
    m_TemperatureMax.UpdateValue(temperature);

    float humidity = GetCurrentHumidityFromSensor();  
    m_CachedHumidity=humidity;
    m_HumidityMin.UpdateValue(humidity);
    m_HumidityMax.UpdateValue(humidity);          
}