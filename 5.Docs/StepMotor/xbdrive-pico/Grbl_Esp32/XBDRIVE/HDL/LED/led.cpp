#include "led.h"

LEDClass::LEDClass()
{

}

LEDClass::~LEDClass()
{
    end();
}

bool LEDClass::begin(uint8_t _ledPin)
{
    ledPin = _ledPin;
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, HIGH);


    return true;
}

void LEDClass::set(uint8_t val)
{
    digitalWrite(ledPin, val);
}


bool LEDClass::end()
{
    pinMode(ledPin, INPUT);

    return true;
}

LEDClass LED;