#ifndef __DRIVERS_H_
#define __DRIVERS_H_

#include <Arduino.h>

class DriversInit_t
{
public:
    uint8_t _refPin;
    uint8_t _IN1Pin;
    uint8_t _IN2Pin;
    DriversInit_t();
};

class DriversClass
{
private:
    uint8_t refPin;
    uint8_t IN1Pin;
    uint8_t IN2Pin;

public:
    DriversClass(void);
    ~DriversClass(void);

    bool begin(DriversInit_t * DriversInit);
    bool begin(uint8_t _IN1Pin, uint8_t _IN2Pin, uint8_t _refPin);
    void set(uint8_t _IN1, uint8_t _IN2);
    void set(uint8_t _IN1, uint8_t _IN2, uint8_t ref);
    void free();
    bool end();
};

extern DriversClass CoilA, CoilB;

#endif
