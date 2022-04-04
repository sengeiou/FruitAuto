#ifndef __POWERVOLTAGE_H_
#define __POWERVOLTAGE_H_

#include <Arduino.h>
#include <XBDRIVE/HDL/DivResVolSamp/DivResVolSamp.h>
#include <driver/adc.h>

class PowerVoltageClass
{
private:
    DivResVolSampClass DivResVolSamp;
    adc1_channel_t ADC1Channel;
public:
    PowerVoltageClass();
    ~PowerVoltageClass();

    bool begin(adc1_channel_t _ADC1Channel);
    float GetVolt();
    void end();
};

extern PowerVoltageClass PowerVoltage;

#endif
