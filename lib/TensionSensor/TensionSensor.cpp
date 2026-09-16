#include "TensionSensor.h"
#include "ADS1220.h"

TensionSensor::TensionSensor(int index,int cspin, int drdypin, float lccal)
    : _index(index),
      _cspin(cspin),
      _drdypin(drdypin),
      _lc_cal(lccal),
      _adc(cspin, drdypin) {
}

void TensionSensor::start_sensor() {
    Serial.println(">> TENSION SENSOR " + String(_index));

    Serial.println("Initializing ADS1220...");
    _adc.begin();
    _adc.reset();
    _adc.writeRegister(0x00, AIN0_AIN3_GAIN128);     // DO NOT CHANGE for the custom break out boards
    _adc.writeRegister(0x01, DRATE_2K);              // Use this to change the sample rate
    _adc.startConversion();
    Serial.println("Conversion started, waiting for DRDY...");

    // Zero the offset with 100 samples --> sets the initial position as zero.
    _adc.findADCOffset(100);

    Serial.println("SETUP COMPLETE");
}

void TensionSensor::update_force() {
    _force = _adc.readDataCalibrated(_lc_cal); 
}

float TensionSensor::reading() {return _force;}
int TensionSensor::getdrdypin() {return _drdypin;}