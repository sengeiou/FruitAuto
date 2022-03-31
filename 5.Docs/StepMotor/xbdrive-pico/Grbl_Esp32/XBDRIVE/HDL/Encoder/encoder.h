#ifndef __ENCODER_H_
#define __ENCODER_H_

#include <Arduino.h>
#include <SPI.h>

#define SPI_CLK_SPEED 10000000
#define SPI_MODE SPI_MODE3

class EncoderInit_t
{
public:
    int8_t sck;
    int8_t miso;
    int8_t mosi;
    int8_t cs;
    EncoderInit_t();
};

class EncoderClass
{
private:
    SPISettings settings;
    SPIClass *spi;
    int cs;
    int spi_mode;
    long clock_speed;
    int bit_resolution;
    int angle_register;

public:
    EncoderClass(uint8_t spi_num = VSPI, int _cs = 5);
    ~EncoderClass(void);

    bool begin();
    bool begin(uint8_t spi_num, int _cs);
    bool begin(int8_t sck, int8_t miso, int8_t mosi, int8_t ss);
    bool begin(EncoderInit_t * EncoderInit);
    void setHwCs(bool use);
    int32_t IRAM_ATTR ReadAngle();
    int32_t IRAM_ATTR ReadAngleHwCs();
    int32_t IRAM_ATTR ReadAngleHwCsYORO();
    bool end();
};

extern EncoderClass Encoder;

#endif
