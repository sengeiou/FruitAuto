#ifndef __NTC_H_
#define __NTC_H_

#include <Arduino.h>
#include <math.h>

#define TAB_LENGTH 200

// 摄氏度
class NTCClass
{
private:
    uint32_t resolution;
    float Vref;
    float VCC;
    uint32_t divRes;
    uint32_t NTCRes;
    uint32_t BVal;

    uint16_t Temp2Res_Tab[TAB_LENGTH];
public:
    NTCClass();
    ~NTCClass();

    bool begin(uint32_t _resolution, float _VCC, float _Vref, uint32_t _divRes, uint32_t _NTCRes, uint32_t _BVal);
    float GetTemp(uint32_t ADCVal);
};

#endif