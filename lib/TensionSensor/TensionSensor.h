#include <Arduino.h>
#include <SPI.h>
#include "ADS1220.h"

class TensionSensor {
    public:
        TensionSensor(int index,int cspin, int drdypin, float lccal);
        void start_sensor();
        void update_force();
        float reading();
        int getdrdypin();
    
    private:
        int _index;
        int _cspin;
        int _drdypin;
        float _lc_cal;
        float _force = 0.0f;
        ADS1220 _adc;
    };