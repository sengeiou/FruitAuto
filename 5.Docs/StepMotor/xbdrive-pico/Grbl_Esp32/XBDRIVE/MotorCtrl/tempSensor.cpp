#include "tempSensor.h"

TempSensorClass::TempSensorClass()
{
}
TempSensorClass::~TempSensorClass()
{
}

bool TempSensorClass::begin(adc1_channel_t _ADC1Channel)
{
    NTC.begin(4096, 3.3, 3.6, 1000, 10000, 3950);
    ADC1Channel = _ADC1Channel;
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1Channel, ADC_ATTEN_DB_11);

    return true;
}
float TempSensorClass::GetTemp()
{
    return NTC.GetTemp(adc1_get_raw(ADC1Channel));
}
void TempSensorClass::end()
{

}

TempSensorClass TempSensor;