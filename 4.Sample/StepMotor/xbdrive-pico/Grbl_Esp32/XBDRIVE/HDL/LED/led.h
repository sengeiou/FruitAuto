#ifndef __LED_H_
#define __LED_H_
#include <Arduino.h>

class LEDClass
{
private:
    uint8_t ledPin;

public:
    LEDClass(void);
    ~LEDClass(void);

    bool begin(uint8_t _ledPin);
    void set(uint8_t val);
    bool end();
};

extern LEDClass LED;

#endif
