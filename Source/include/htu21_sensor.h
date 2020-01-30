
#ifndef __htu21_sensor_H_
#define __htu21_sensor_H_

#include <Arduino.h>

void htu21_sensor_setup();

float GetTemperature();
float GetHumidity();

String GetTemperatureStr();
String GetHumidityStr();

#endif