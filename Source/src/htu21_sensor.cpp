//Necessary to make temp sensor working properly

#include "definitions.h"
#include "htu21_sensor.h"

void HTU21Sensor::Setup()
{
    m_Wire.begin(SDA_PIN, SCL_PIN);
    m_HTU21Sensor.begin(m_Wire);

    Serial.print("Init Done");
    Serial.println();
    float humd = m_HTU21Sensor.readHumidity();
  float temp = m_HTU21Sensor.readTemperature();

  Serial.print("Time:");
  Serial.print(millis());
  Serial.print(" Temperature:");
  Serial.print(temp, 1);
  Serial.print("C");
  Serial.print(" Humidity:");
  Serial.print(humd, 1);
  Serial.print("%");

  Serial.println();

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