/********************************************************************************
* @Filename:        PowerVoltage.cpp
* @Author:          
* @Version:         ver1.0
* @Date:            2021-5-9
* @Description:     
* @History:         
********************************************************************************/
#include "PowerVoltage.h"

PowerVoltageClass::PowerVoltageClass()
{
}
PowerVoltageClass::~PowerVoltageClass()
{
}

bool PowerVoltageClass::begin(adc1_channel_t _ADC1Channel)
{
    DivResVolSamp.begin(4096, 3.6, 1000, 10000);
    ADC1Channel = _ADC1Channel;
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1Channel, ADC_ATTEN_DB_11);

    return true;
}
float PowerVoltageClass::GetVolt()
{
    return DivResVolSamp.GetVolt(adc1_get_raw(ADC1Channel));
}
void PowerVoltageClass::end()
{

}

PowerVoltageClass PowerVoltage;