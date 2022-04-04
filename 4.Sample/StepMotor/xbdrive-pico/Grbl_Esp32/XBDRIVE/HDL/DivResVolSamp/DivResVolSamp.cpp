/********************************************************************************
* @Filename:        DivResVolSamp.cpp
* @Author:          矛盾聚合体
* @Version:         ver1.0
* @Date:            2021-5-9
* @Description:     
* @History:         
********************************************************************************/
#include "DivResVolSamp.h"
#include <math.h>

DivResVolSampClass::DivResVolSampClass()
{
}
DivResVolSampClass::~DivResVolSampClass()
{
}

bool DivResVolSampClass::begin(uint32_t _resolution, float _Vref, uint32_t _divResL, uint32_t _divResH)
{
    resolution = _resolution;
    Vref = _Vref;
    divResL = _divResL;
    divResH = _divResH;

    return true;
}
float DivResVolSampClass::GetVolt(uint32_t ADCVal)
{
    return (ADCVal * 1.0 / resolution * 3.6)*(divResL + divResH)/divResL;
}
void DivResVolSampClass::end()
{

}