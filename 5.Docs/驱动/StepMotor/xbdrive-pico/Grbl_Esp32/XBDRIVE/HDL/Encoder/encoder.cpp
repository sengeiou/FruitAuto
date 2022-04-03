/********************************************************************************
* @Filename:        encoder.cpp
* @Author:          
* @Version:         ver1.0
* @Date:            2021-5-9
* @Description:     
* @History:         
********************************************************************************/
#include "encoder.h"

EncoderClass::EncoderClass(uint8_t spi_num, int _cs) {
    spi = new SPIClass(spi_num);
    cs  = _cs;
}

EncoderClass::~EncoderClass() {
    end();
}

bool EncoderClass::begin() {
    settings = SPISettings(SPI_CLK_SPEED, MSBFIRST, SPI_MODE);
    spi->begin();
    pinMode(cs, OUTPUT);

    return true;
}

bool EncoderClass::begin(EncoderInit_t* EncoderInit) {
    return begin(EncoderInit->sck, EncoderInit->miso, EncoderInit->mosi, EncoderInit->cs);
}

bool EncoderClass::begin(uint8_t spi_num, int _cs) {
    spi      = new SPIClass(spi_num);
    cs       = _cs;
    settings = SPISettings(SPI_CLK_SPEED, MSBFIRST, SPI_MODE);
    spi->begin();
    pinMode(cs, OUTPUT);

    return true;
}

bool EncoderClass::begin(int8_t sck, int8_t miso, int8_t mosi, int8_t ss) {
    int8_t res = 0;
    // 判断传入参数合法性
    if (sck == GPIO_NUM_MAX)
        res++;
    if (miso == GPIO_NUM_MAX)
        res++;
    if (mosi == GPIO_NUM_MAX)
        res++;
    if (ss == GPIO_NUM_MAX)
        res++;
    settings = SPISettings(SPI_CLK_SPEED, MSBFIRST, SPI_MODE);
    spi->begin(sck, miso, mosi, ss);
    pinMode(cs, OUTPUT);

    return !res;
}

void EncoderClass::setHwCs(bool use) {
    spi->setHwCs(use);
}

int32_t IRAM_ATTR EncoderClass::ReadAngle() {
    spi->beginTransaction(settings);
    digitalWrite(5, LOW);
    uint16_t register_value0 = spi->transfer16(0x8300);
    digitalWrite(5, HIGH);
    digitalWrite(5, LOW);
    uint16_t register_value1 = spi->transfer16(0x8400);
    digitalWrite(5, HIGH);
    spi->endTransaction();

    int32_t res = 0;
    res         = (register_value0 << 6) + (register_value1 >> 2);

    return res;
}

int32_t IRAM_ATTR EncoderClass::ReadAngleHwCs() {
    spi->beginTransaction(settings);
    uint16_t register_value0 = spi->transfer16(0x8300);
    uint16_t register_value1 = spi->transfer16(0x8400);
    spi->endTransaction();

    int32_t res = 0;
    res         = (register_value0 << 6) + (register_value1 >> 2);

    return res;
}

int32_t IRAM_ATTR EncoderClass::ReadAngleHwCsYORO() {
    spi->beginTransaction(settings);
    uint32_t register_value = spi->transfer32(0x83840000);
    spi->endTransaction();

    int32_t res = 0;
    res         = (register_value & 0x00ffff00) >> 10;

    return res;
}

bool EncoderClass::end() {
    spi->end();
    pinMode(cs, INPUT);

    return true;
}

EncoderInit_t::EncoderInit_t() {
    sck  = GPIO_NUM_MAX;
    miso = GPIO_NUM_MAX;
    mosi = GPIO_NUM_MAX;
    cs   = GPIO_NUM_MAX;
};

EncoderClass Encoder(VSPI, 5);