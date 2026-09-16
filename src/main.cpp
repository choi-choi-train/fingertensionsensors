#include <Arduino.h>
#include <SPI.h>
#include "ADS1220.h"
#include "TensionSensor.h"

// Initialize tension sensors with corresponding CS and DRDY pins
// Calibration factors: (Vref / gain) / (2^23) — tune to your load cell
TensionSensor ts1(30, 31, 1.0f);
TensionSensor ts2(32, 33, 1.0f);
TensionSensor ts3(34, 35, 1.0f);
TensionSensor ts4(36, 37, 1.0f);
void sensor1_read() {ts1.update_force();}
void sensor2_read() {ts2.update_force();}
void sensor3_read() {ts3.update_force();}
void sensor4_read() {ts4.update_force();}

void setup() {
    Serial.begin(115200);
    while (!Serial) {}
    Serial.println("Teensy booted");

    ts1.start_sensor();
    ts2.start_sensor();
    ts3.start_sensor();
    ts4.start_sensor();

    SPI.begin();
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE1));

    attachInterrupt(ts1.getdrdypin(), sensor1_read, FALLING); 
    attachInterrupt(ts2.getdrdypin(), sensor2_read, FALLING); 
    attachInterrupt(ts3.getdrdypin(), sensor3_read, FALLING); 
    attachInterrupt(ts4.getdrdypin(), sensor4_read, FALLING); 

    delay(2000);
}

void loop() {
    // Read out the load cell measurements @ 10 Hz
    noInterrupts();
    float force_1 = ts1.reading();
    float force_2 = ts2.reading();
    float force_3 = ts3.reading();
    float force_4 = ts4.reading();
    interrupts();

    Serial.print(force_1);
    Serial.print(",");
    Serial.print(force_2);
    Serial.print(",");
    Serial.print(force_3);
    Serial.print(",");
    Serial.println(force_4);

    delay(100);
}