
#ifndef __htu21_sensor_H_
#define __htu21_sensor_H_

#include <Arduino.h>

void htu21_sensor_setup();

float GetTemperature();
float GetTemperatureMax();
float GetTemperatureMin();

float GetHumidity();
float GetHumidityMax();
float GetHumidityMin();

String GetTemperatureStr();
String GetHumidityStr();

String GetTemperatureMaxStr();
String GetTemperatureMinStr();

String GetHumidityMaxStr();
String GetHumidityMinStr();

#endif