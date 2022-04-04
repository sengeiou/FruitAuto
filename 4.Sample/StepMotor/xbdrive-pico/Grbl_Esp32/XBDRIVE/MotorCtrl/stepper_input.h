#ifndef __STEPPER_INPUT_H
#define __STEPPER_INPUT_H

#include <Arduino.h>
#include <XBDRIVE/HDL/PCNT/pulsecnt.h>

#define DIR_FORWARD_LEVEL LOW
#define ENN_ENABLE_LEVEL LOW

class StepperInputInit_t {
public:
    void (*_ENN_callBack)(void);
    uint8_t _ENN_Pin;
    uint8_t _STEP_Pin;
    uint8_t _DIR_Pin;
    uint8_t _ENN_Active_Level;

    StepperInputInit_t();
};

class StepperInputClass {
private:
    PulseCNTClass PulseCNT;
    uint8_t       STEP_Pin;
    uint8_t       DIR_Pin;
    uint8_t       ENN_Pin;
    uint8_t       ENN_Active_Level;

public:
    StepperInputClass(void);
    ~StepperInputClass(void);

    void (*ENN_callBack)(void) = NULL;

    bool    begin(void (*_ENN_callBack)(void), uint8_t _ENN_Pin, uint8_t ENN_Active_Level, uint8_t _STEP_Pin, uint8_t _DIR_Pin);
    bool    begin(StepperInputInit_t* StepperInputInit);
    bool    IsEnlable();
    bool    IsCCW();
    int32_t GetIntputPulse();
    bool    end(void);
};

extern StepperInputClass StepperInput;

#endif
