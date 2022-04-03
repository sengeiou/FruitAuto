#ifndef __TEMPSENSOR_H_
#define __TEMPSENSOR_H_

#include <Arduino.h>
#include <XBDRIVE/HDL/NTC/ntc.h>
#include <driver/adc.h>

// 摄氏度
class TempSensorClass
{
private:
    NTCClass NTC;
    adc1_channel_t ADC1Channel;
public:
    TempSensorClass();
    ~TempSensorClass();

    bool begin(adc1_channel_t _ADC1Channel);
    float GetTemp();
    void end();
};

extern TempSensorClass TempSensor;

#endif