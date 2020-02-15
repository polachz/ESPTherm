#ifndef __min_max_H_
#define __min_max_H_

class ESPThermTimeDate;

class ValueWithTimeStamp
{
    class MinMaxBase;
public:
    ValueWithTimeStamp(ESPThermTimeDate& timeDateObj, float initVal=0):
    m_ESPtimeDateObj(timeDateObj),
        m_Value(initVal), 
        m_TimeStamp(0) {}

    float           Value() const {return m_Value;}
    unsigned long   TimeStamp()const {return m_TimeStamp;}
protected:

    void SetValue(float value);

    ESPThermTimeDate& TimeObj(){ return m_ESPtimeDateObj;}

    ESPThermTimeDate& m_ESPtimeDateObj;

    float           m_Value;
    unsigned long   m_TimeStamp; //Seconds since Epoch (POSIX time)

    
};


class MinMaxBase : public ValueWithTimeStamp
{
public:
    MinMaxBase(ESPThermTimeDate& timeDateObj, float initVal): 
        ValueWithTimeStamp(timeDateObj,initVal)
        {}

    virtual void UpdateValue(float value)=0;

    const ValueWithTimeStamp& GetValueAndStamp()const { return *this;}
    
};


class CMinValue : public MinMaxBase
{
public:
    CMinValue(ESPThermTimeDate& timeDateObj):MinMaxBase(timeDateObj, 1000){}

    virtual void UpdateValue(float value) override;
};


class CMaxValue : public MinMaxBase
{
public:
    CMaxValue(ESPThermTimeDate& timeDateObj):MinMaxBase(timeDateObj, -1000){}

    virtual void UpdateValue(float value) override;
};

#endif