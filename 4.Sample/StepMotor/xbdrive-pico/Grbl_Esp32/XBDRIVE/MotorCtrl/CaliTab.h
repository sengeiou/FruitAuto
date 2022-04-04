#ifndef __CALITAB_H_
#define __CALITAB_H_
#include <nvs.h>
#include <nvs_flash.h>
#include "FS.h"
#include "SPIFFS.h"
#include <string.h>

#define CALITABLE_PATH "/calitab.bin"
#define CALITABLE_LENGTH 32*1024/2

class CaliTabClass
{
private:
    uint16_t CaliTable[CALITABLE_LENGTH];

public:
    CaliTabClass(void);
    ~CaliTabClass(void);
    bool begin(void);
    bool clear(void);
    bool set(uint16_t index, uint16_t val);
    uint16_t IRAM_ATTR get(uint16_t index);
    bool loadCaliTable(void);
    bool saveCaliTable(void);
    bool end(void);
};

extern CaliTabClass CaliTab;

#endif
