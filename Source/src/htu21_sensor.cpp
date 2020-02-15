//Necessary to make temp sensor working properly

#include "definitions.h"
#include "htu21_sensor.h"

void HTU21Sensor::Setup()
{
    m_Wire.begin(SDA_PIN, SCL_PIN);
    m_Sensor.begin(m_Wire);
}

float HTU21Sensor::GetCurrentTemperatureFromSensor()
{
    return HTUSensor().readTemperature();
}
float HTU21Sensor::GetCurrentHumidityFromSensor()
{
    return HTUSensor().readHumidity();
}