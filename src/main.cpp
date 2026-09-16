#include <Arduino.h>
#include <SPI.h>
#include "ADS1220.h"
#include "TensionSensor.h"

// Initialize tension sensors with corresponding CS and DRDY pins
// Calibration factors: (Vref / gain) / (2^23) — tune to your load cell
TensionSensor ts1(1, 33, 34, (1.0/(1<<23)));
TensionSensor ts2(2, 35, 36, (1.0/(1<<23)));
TensionSensor ts3(3, 39, 40, (1.0/(1<<23)));
TensionSensor ts4(4, 22, 23, (1.0/(1<<23)));
void sensor1_read() {ts1.update_force();}
void sensor2_read() {ts2.update_force();}
void sensor3_read() {ts3.update_force();}
void sensor4_read() {ts4.update_force();}

void setup() {
    Serial.begin(115200);
    while (!Serial) {}
    Serial.println("Teensy booted");

    SPI.begin();
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE1));

    ts1.start_sensor();
    ts2.start_sensor();
    ts3.start_sensor();
    ts4.start_sensor();

    attachInterrupt(ts1.getdrdypin(), sensor1_read, FALLING); 
    attachInterrupt(ts2.getdrdypin(), sensor2_read, FALLING); 
    attachInterrupt(ts3.getdrdypin(), sensor3_read, FALLING); 
    attachInterrupt(ts4.getdrdypin(), sensor4_read, FALLING); 

    delay(2000);
}

void loop() {
    // Read out the load cell measurements @ 10 Hz
    noInterrupts();
    float force_1 = abs(ts1.reading());
    float force_2 = abs(ts2.reading());
    float force_3 = abs(ts3.reading());
    float force_4 = abs(ts4.reading());
    interrupts();

    Serial.println(String(force_1) + "," + String(force_2) + "," + String(force_3) + "," + String(force_4));

    delay(100);
}