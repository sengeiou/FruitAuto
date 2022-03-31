#include "CaliTab.h"

CaliTabClass::CaliTabClass()
{
}

CaliTabClass::~CaliTabClass()
{
    end();
}

bool CaliTabClass::begin()
{
    return SPIFFS.begin(true);
}

bool CaliTabClass::clear()
{
    memset(CaliTable, 0, CALITABLE_LENGTH * sizeof(CaliTable[0]));
    if(SPIFFS.exists(CALITABLE_PATH))
    {
        SPIFFS.remove(CALITABLE_PATH);
    }

    return true;
}

bool CaliTabClass::set(uint16_t index, uint16_t val)
{
    CaliTable[index] = val;

    return true;
}

uint16_t IRAM_ATTR CaliTabClass::get(uint16_t index)
{
    return CaliTable[index];
}

bool CaliTabClass::loadCaliTable(void)
{
    File file = SPIFFS.open(CALITABLE_PATH, FILE_READ);
    if (!file)
    {
        return false;
    }
    file.read((uint8_t *)CaliTable, CALITABLE_LENGTH * sizeof(CaliTable[0]));
    file.close();

    return true;
}

bool CaliTabClass::saveCaliTable(void)
{
    File file = SPIFFS.open(CALITABLE_PATH, FILE_WRITE);
    if (!file)
    {
        return false;
    }
    file.write((uint8_t *)CaliTable, CALITABLE_LENGTH * sizeof(CaliTable[0]));
    file.close();

    return true;
}

bool CaliTabClass::end(void)
{
    SPIFFS.end();

    return true;
}

CaliTabClass CaliTab;