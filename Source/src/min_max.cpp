#include <Arduino.h>
#include "debug.h"

#include "esp_therm_time_date.h"
#include "min_max.h"


void ValueWithTimeStamp::SetValue(float value)
{
    m_Value = value;
    unsigned long et = TimeObj().EpochTime();
    if(et>946684800){
        m_TimeStamp = et;
    }
}


void CMinValue::UpdateValue(float value)
{
    if(value < m_Value ){
        SetValue(value);
    }
}

void CMaxValue::UpdateValue(float value)
{
    if(value > m_Value ){
        SetValue(value);
    }
}
