#include "stepper_input.h"

portMUX_TYPE muxENN = portMUX_INITIALIZER_UNLOCKED;
uint8_t      o_ENN_Pin;
uint8_t      o_ENN_Active_Level;

void IRAM_ATTR ENN_IRQ_callback() {
    portENTER_CRITICAL_ISR(&muxENN);
    // 执行回调函数
    if (reinterpret_cast<StepperInputClass*>(&StepperInput)->ENN_callBack != NULL)
        reinterpret_cast<StepperInputClass*>(&StepperInput)->ENN_callBack();
    portEXIT_CRITICAL_ISR(&muxENN);
}

StepperInputClass::StepperInputClass() {}
StepperInputClass::~StepperInputClass() {
    end();
}

bool StepperInputClass::begin(StepperInputInit_t* StepperInputInit) {
    return begin(StepperInputInit->_ENN_callBack,
                 StepperInputInit->_ENN_Pin,
                 StepperInputInit->_ENN_Active_Level,
                 StepperInputInit->_STEP_Pin,
                 StepperInputInit->_DIR_Pin);
}

bool StepperInputClass::begin(void (*_ENN_callBack)(void), uint8_t _ENN_Pin, uint8_t ENN_Active_Level, uint8_t _STEP_Pin, uint8_t _DIR_Pin) {
    int8_t res = 0;
    // 判断传入参数合法性
    if (_ENN_callBack == NULL) {
        res++;
    }
    if (_ENN_Pin == GPIO_NUM_MAX) {
        res++;
    }
    if (ENN_Active_Level != HIGH && ENN_Active_Level != LOW) {
        res++;
    }
    if (_STEP_Pin == GPIO_NUM_MAX) {
        res++;
    }
    if (_DIR_Pin == GPIO_NUM_MAX) {
        res++;
    }
    // 参数传递
    ENN_callBack = _ENN_callBack;
    STEP_Pin     = _STEP_Pin;
    DIR_Pin      = _DIR_Pin;
    ENN_Pin      = _ENN_Pin;
    // 外部变量初始化
    o_ENN_Pin          = ENN_Pin;
    o_ENN_Active_Level = ENN_Active_Level;
    // 初始化ENN引脚并注册回调函数
    pinMode(ENN_Pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ENN_Pin), ENN_IRQ_callback, CHANGE);
    // 初始化外部脉冲计数器
    PulseCNTInit_t PulseCNTInit;
    PulseCNTInit._PCNT_Dir_Pin   = DIR_Pin;
    PulseCNTInit._PCNT_Pulse_Pin = STEP_Pin;
    PulseCNTInit._maxcnt         = 32000;
    // res += PulseCNT.init(&PulseCNTInit);

    if (PulseCNT.init(&PulseCNTInit) == false) {
        res++;
    }

    return !res;
}

bool StepperInputClass::IsEnlable() {
    return digitalRead(ENN_Pin) == ENN_Active_Level;
}

bool StepperInputClass::IsCCW() {
    return !!digitalRead(DIR_Pin);
}

int32_t StepperInputClass::GetIntputPulse() {
    return PulseCNT.getCnt();
}

bool StepperInputClass::end() {
    return true;
}

StepperInputInit_t::StepperInputInit_t() {
    _ENN_callBack     = NULL;
    _ENN_Pin          = GPIO_NUM_MAX;
    _STEP_Pin         = GPIO_NUM_MAX;
    _DIR_Pin          = GPIO_NUM_MAX;
    _ENN_Active_Level = LOW;
}

StepperInputClass StepperInput;