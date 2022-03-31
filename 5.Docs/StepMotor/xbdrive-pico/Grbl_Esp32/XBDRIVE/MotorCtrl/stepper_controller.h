#ifndef __STEPPER_CONTROLLER_H
#define __STEPPER_CONTROLLER_H

#include <Arduino.h>
#include "esp_task_wdt.h"
#include "driver/timer.h"

class StepperControllerClass
{
private:

public:
    StepperControllerClass(void);
    ~StepperControllerClass(void);
    void (*callBackFun)(void) = NULL;
    bool begin(void (*_callBackFun)(void));
    bool resume(void);
    bool suspend(void);
    bool end(void);
};

extern StepperControllerClass StepCtrl;

#endif
