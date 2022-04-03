#include "drivers.h"

DriversClass::DriversClass()
{
    refPin = GPIO_NUM_MAX;
    IN1Pin = GPIO_NUM_MAX;
    IN2Pin = GPIO_NUM_MAX;
}

DriversClass::~DriversClass()
{
    end();
}

bool DriversClass::begin(DriversInit_t * DriversInit)
{
    return begin(DriversInit->_IN1Pin, DriversInit->_IN2Pin, DriversInit->_refPin);
}

bool DriversClass::begin(uint8_t _IN1Pin, uint8_t _IN2Pin, uint8_t _refPin)
{
    int8_t res = 0;
    // 判断传入参数合法性
    if (_IN1Pin == GPIO_NUM_MAX)
        res++;
    if (_IN2Pin == GPIO_NUM_MAX)
        res++;
    if (_refPin != GPIO_NUM_25 && _refPin != GPIO_NUM_26)
        res++;
    // 参数传递
    refPin = _refPin;
    IN1Pin = _IN1Pin;
    IN2Pin = _IN2Pin;
    // IO初始化
    pinMode(IN1Pin, OUTPUT);
    pinMode(IN2Pin, OUTPUT);
    dacWrite(refPin, 0);
    digitalWrite(IN1Pin, LOW);
    digitalWrite(IN2Pin, LOW);

    return !res;
}

void DriversClass::set(uint8_t _IN1, uint8_t _IN2)
{
    digitalWrite(IN1Pin, _IN1);
    digitalWrite(IN2Pin, _IN2);
}

void DriversClass::set(uint8_t _IN1, uint8_t _IN2, uint8_t ref)
{
    digitalWrite(IN1Pin, _IN1);
    digitalWrite(IN2Pin, _IN2);
    dacWrite(refPin, ref);
}

void DriversClass::free()
{
    set(LOW, LOW, 0);
}

bool DriversClass::end()
{
    pinMode(IN1Pin, INPUT);
    pinMode(IN2Pin, INPUT);

    return true;
}

DriversInit_t::DriversInit_t()
{
    _refPin = GPIO_NUM_MAX;
    _IN1Pin = GPIO_NUM_MAX;
    _IN2Pin = GPIO_NUM_MAX;
}

DriversClass CoilA, CoilB;