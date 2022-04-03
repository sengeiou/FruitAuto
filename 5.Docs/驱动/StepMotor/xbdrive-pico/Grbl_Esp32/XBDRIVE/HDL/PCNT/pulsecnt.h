#ifndef __PULSECNT_H_
#define __PULSECNT_H_

#include <Arduino.h>
#include <driver/pcnt.h>

class PulseCNTInit_t
{
    public:
    uint8_t _PCNT_Pulse_Pin;
    uint8_t _PCNT_Dir_Pin;
    int16_t _maxcnt;
    pcnt_unit_t _PCNT_Unit;

    PulseCNTInit_t();
};

class PulseCNTClass
{
private:
    pcnt_unit_t PCNT_Unit;
    uint8_t PCNT_Pulse_Pin;
    uint8_t PCNT_Dir_Pin;
    int16_t maxcnt;
    uint32_t IND_Overflow;
    uint32_t DEC_Overflow;
public:
    PulseCNTClass(void);
    ~PulseCNTClass(void);

    bool init(uint8_t _PCNT_Pulse_Pin, uint8_t _PCNT_Dir_Pin, int16_t _maxcnt, pcnt_unit_t _PCNT_Unit = PCNT_UNIT_0);
    bool init(PulseCNTInit_t * PulseCNTInit);
    bool begin();
    bool pause();
    bool resume();
    bool clear();
    int32_t getCnt();
    bool end();
};

#endif
