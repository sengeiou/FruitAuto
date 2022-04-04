#ifndef __OPERATIONMODE_H_
#define __OPERATIONMODE_H_

#include <Arduino.h>

class OperationalModeInit_t
{
public:
    void (*_OperationalModeCheak)(void);
    uint8_t _SET1_PIN;
    uint8_t _SET2_PIN;
    uint8_t _OPCL_PIN;
    uint8_t _CALI_PIN;

    OperationalModeInit_t();
};

class OperationalModeClass
{
private:
    uint8_t SET1_PIN;
    uint8_t SET2_PIN;
    uint8_t OPCL_PIN;
    uint8_t CALI_PIN;
    void (*OperationalModeCheak)(void);

public:
    uint8_t SET1;
    uint8_t SET2;
    uint8_t OPCL;
    uint8_t CALI;
    OperationalModeClass(void);
    ~OperationalModeClass(void);
    bool begin(OperationalModeInit_t * OperationalModeInit);
    bool begin(void (*_OperationalModeCheak)(void), uint8_t _SET1_PIN, uint8_t _SET2_PIN, uint8_t _OPCL_PIN, uint8_t _CALI_PIN);
    void cheak(void);
    bool end(void);
};

extern OperationalModeClass OperationalMode;

#endif
