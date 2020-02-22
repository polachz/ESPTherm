//Necessary to make temp sensor working properly

#include "definitions.h"
#include "htu21_sensor.h"

void HTU21Sensor::Setup()
{
    m_Wire.begin(SDA_PIN, SCL_PIN);
    m_HTU21Sensor.begin(m_Wire);
}

float HTU21Sensor::GetCurrentTemperatureFromSensor()
{
    if(UseCelsius()){
        return HTUSensor().readTemperature();
    }else{
        return CelsiusToFarenheit(HTUSensor().readTemperature());
    }
}
float HTU21Sensor::GetCurrentHumidityFromSensor()
{
    return HTUSensor().readHumidity();
}