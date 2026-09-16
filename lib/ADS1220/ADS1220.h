#ifndef ADS1220_H
#define ADS1220_H

#include <SPI.h>

#define RESET 0x06
#define START 0x08
#define PDWN  0x02
#define RDATA 0x10
#define RREG  0x20
#define WREG  0x40

#define AIN0_AIN3_GAIN128 0x2E

#define DRATE_2K 0xD4
#define DRATE_1K 0xC4
#define DRATE_90 0x44
#define DRATE_20 0x04 


class ADS1220 {
public:
    ADS1220(int cs_pin, int drdy_pin);
    void begin();
    void reset();
    void writeRegister(uint8_t address, uint8_t value);
    uint8_t readRegister(uint8_t address);
    int32_t readData();
    float readDataCalibrated(float loadcell_cal);
    void startConversion();
    void powerDown();
    void findADCOffset(int32_t num_samples);

private:
    int _cs_pin;
    int _drdy_pin;
    int32_t _lc_offset = 0;
    void spi_command(uint8_t command);
};

#endif // ADS1220_H