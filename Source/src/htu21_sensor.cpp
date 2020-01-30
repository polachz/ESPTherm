//Necessary to make temp sensor working properly
#include "definitions.h"
#include <Wire.h>
#include "SparkFunHTU21D.h"

// ***************************************************************************
// Global objects for temperature sensor
// ***************************************************************************
HTU21D myHumidity;
TwoWire myWire;

void htu21_sensor_setup()
{
    myWire.begin(SDA_PIN, SCL_PIN);
    myHumidity.begin(myWire);
}
float GetTemperature()
{
    return myHumidity.readTemperature();
}

float GetHumidity()
{
    return myHumidity.readHumidity();    
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