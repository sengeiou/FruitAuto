#include "ntc.h"
#include <math.h>

NTCClass::NTCClass()
{
}

NTCClass::~NTCClass()
{
}

bool NTCClass::begin(uint32_t _resolution, float _VCC, float _Vref, uint32_t _divRes, uint32_t _NTCRes, uint32_t _BVal)
{
    resolution = _resolution;
    Vref = _Vref;
    VCC = _VCC;
    divRes = _divRes;
    NTCRes = _NTCRes;
    BVal = _BVal;
    // =FLOOR(10000*EXP(3950*(1/(A1+273.15)-1/(25+273.15))),1)
    for (int i = 0; i < TAB_LENGTH; i++)
    {
        Temp2Res_Tab[i] = NTCRes * exp(BVal * ((1 / (i + 273.15) - 1 / (25 + 273.15))));
    }

    return true;
}

float NTCClass::GetTemp(uint32_t ADCVal)
{
    uint32_t NTCResVal = divRes * VCC / (ADCVal * 1.0 / resolution * 3.6) - divRes;
    // 二分法查表
    uint16_t index_H = TAB_LENGTH - 1;
    uint16_t index_L = 0;
    while (1)
    {
        if (index_L == index_H - 1)
        {
            break;
        }
        if (NTCResVal > Temp2Res_Tab[(index_H + index_L) / 2])
        {
            index_H = (index_H + index_L) / 2;
        }
        else
        {
            index_L = (index_H + index_L) / 2;
        }
    }
    // 线性插值
    return (Temp2Res_Tab[index_L] - NTCResVal) * 1.0 / (Temp2Res_Tab[index_L] - Temp2Res_Tab[index_H]) + index_L;
}
