#include <Arduino.h>
#include "debug.h"

#include "esp_therm_time_date.h"
#include "min_max.h"


void ValueWithTimeStamp::SetValue(float value)
{
    m_Value = value;
    m_TimeStamp = TimeObj().EpochTime();
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
