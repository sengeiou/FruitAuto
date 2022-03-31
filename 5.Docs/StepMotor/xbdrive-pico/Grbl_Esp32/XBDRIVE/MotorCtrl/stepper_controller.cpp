#include "stepper_controller.h"

hw_timer_t *timer = NULL;
// portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR timer_callback()
{
    // portENTER_CRITICAL_ISR(&timerMux);
    if (reinterpret_cast<StepperControllerClass *>(&StepCtrl)->callBackFun != NULL)
        reinterpret_cast<StepperControllerClass *>(&StepCtrl)->callBackFun();
    // portEXIT_CRITICAL_ISR(&timerMux);
}

StepperControllerClass::StepperControllerClass()
{
}
StepperControllerClass::~StepperControllerClass()
{
    end();
}

bool StepperControllerClass::begin(void (*_callBackFun)(void))
{
    // 定时器
    timer = timerBegin(0 /*定时器0*/, 80 /*分频系数80M/80=1M*/, true /*向上计数*/);
    timerAttachInterrupt(timer, &timer_callback /*回调函数*/, true /*边沿触发*/);
    timerAlarmWrite(timer, 100 /*触发阈值1M/50=20k*/, true /*自动重载*/);
    timerAlarmEnable(timer);

    // 注册回调函数
    callBackFun = _callBackFun;

    return true;
}
bool StepperControllerClass::resume()
{
    timerAlarmEnable(timer);

    return true;
}
bool StepperControllerClass::suspend()
{
    timerAlarmDisable(timer);

    return true;
}
bool StepperControllerClass::end()
{
    timerAlarmDisable(timer);
    return true;
}

StepperControllerClass StepCtrl;