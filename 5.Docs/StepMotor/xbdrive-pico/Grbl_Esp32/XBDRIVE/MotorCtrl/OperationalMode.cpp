#include "OperationalMode.h"

OperationalModeClass::OperationalModeClass()
{
}
OperationalModeClass::~OperationalModeClass()
{
}

bool OperationalModeClass::begin(OperationalModeInit_t *OperationalModeInit)
{
    return begin(
        OperationalModeInit->_OperationalModeCheak,
        OperationalModeInit->_SET1_PIN,
        OperationalModeInit->_SET2_PIN,
        OperationalModeInit->_OPCL_PIN,
        OperationalModeInit->_CALI_PIN);
}

bool OperationalModeClass::begin(void (*_OperationalModeCheak)(void), uint8_t _SET1_PIN, uint8_t _SET2_PIN, uint8_t _OPCL_PIN, uint8_t _CALI_PIN)
{
    int8_t res = 0;
    // 判断传入参数合法性
    if (_OperationalModeCheak == NULL)
    {
        res++;
    }
    if (_SET1_PIN == GPIO_NUM_MAX)
    {
        res++;
    }
    if (_SET2_PIN == GPIO_NUM_MAX)
    {
        res++;
    }
    if (_OPCL_PIN == GPIO_NUM_MAX)
    {
        res++;
    }
    if (_CALI_PIN == GPIO_NUM_MAX)
    {
        res++;
    }
    // 参数传递
    OperationalModeCheak = _OperationalModeCheak;
    SET1_PIN = _SET1_PIN;
    SET2_PIN = _SET2_PIN;
    OPCL_PIN = _OPCL_PIN;
    CALI_PIN = _CALI_PIN;
    // 引脚初始化
    pinMode(SET1_PIN, INPUT);
    pinMode(SET2_PIN, INPUT);
    pinMode(OPCL_PIN, INPUT);
    pinMode(CALI_PIN, INPUT);
    // 检查引脚状态
    cheak();
    OperationalModeCheak();

    return true;
}

void OperationalModeClass::cheak()
{
    SET1 = HIGH;
    SET2 = LOW;
    OPCL = LOW;
    CALI = HIGH;
}

bool OperationalModeClass::end()
{
    return true;
}

OperationalModeInit_t::OperationalModeInit_t()
{
    _OperationalModeCheak = NULL;
    _SET1_PIN = GPIO_NUM_MAX;
    _SET2_PIN = GPIO_NUM_MAX;
    _OPCL_PIN = GPIO_NUM_MAX;
    _CALI_PIN = GPIO_NUM_MAX;
}

OperationalModeClass OperationalMode;