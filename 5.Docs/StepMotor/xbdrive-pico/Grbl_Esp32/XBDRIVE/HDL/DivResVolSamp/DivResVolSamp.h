#ifndef __DIVRESVOLSAMP_H_
#define __DIVRESVOLSAMP_H_

#include <Arduino.h>

// 摄氏度
class DivResVolSampClass
{
private:
    uint32_t resolution;
    float Vref;
    uint32_t divResL;
    uint32_t divResH;
public:
    DivResVolSampClass();
    ~DivResVolSampClass();

    bool begin(uint32_t _resolution = 4096, float _Vref = 3.6, uint32_t _divResL = 1000, uint32_t _divResH = 10000);
    float GetVolt(uint32_t ADCVal);
    void end();
};

#endif
