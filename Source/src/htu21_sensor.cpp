//Necessary to make temp sensor working properly
#include "definitions.h"
#include <Wire.h>
#include "SparkFunHTU21D.h"

// ***************************************************************************
// Global objects for temperature sensor
// ***************************************************************************
HTU21D myHumidity;
TwoWire myWire;

float minimum_temperature=100;
float maximum_temperature=-100;

float minimum_humidity=120;
float maximum_humidity=-120;

void htu21_sensor_setup()
{
    myWire.begin(SDA_PIN, SCL_PIN);
    myHumidity.begin(myWire);
}

float GetTemperature()
{
    float temperature = myHumidity.readTemperature();
    if(temperature < minimum_temperature){
        minimum_temperature = temperature;
    }
    if(temperature > maximum_temperature){
        maximum_temperature = temperature;
    }
    return temperature;
}

float GetTemperatureMax()
{
    return maximum_temperature;
}
float GetTemperatureMin()
{
    return minimum_temperature;
}

float GetHumidity()
{
    float humidity = myHumidity.readHumidity();    
    if(humidity < minimum_humidity){
        minimum_humidity = humidity;
    }
    if(humidity > maximum_humidity){
        maximum_humidity = humidity;
    }
    return humidity;
}

float GetHumidityMax()
{
    return maximum_humidity;
}

float GetHumidityMin()
{
    return minimum_humidity;
}

String GetTemperatureStr()
{
    static int x =10;
    if(x<30){
        x=x+1;
    }else{
        x=10;
    }
    //return String(myHumidity.readTemperature());
    return String(x);
}

String GetHumidityStr()
{
    //return String(myHumidity.readHumidity());    
    static int x =50;
    if(x<70){
        x=x+1;
    }else{
        x=50;
    }
    return String(x);
}

String GetTemperatureMaxStr(){
    return String(GetTemperatureMax());
}

String GetTemperatureMinStr(){
    return String(GetTemperatureMin());
}

String GetHumidityMaxStr(){
    return String(GetHumidityMax());
}

String GetHumidityMinStr(){
    return String(GetHumidityMin());
}