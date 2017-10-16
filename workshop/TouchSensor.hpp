#ifndef _TOUCHSENSOR_HPP_
#define _TOUCHSENSOR_HPP_

#include "Sensor.hpp"
#include <Wire.h> // include I2C library
#include <i2c_touch_sensor.h>

#define N_TOUCHPADS 4

class TouchSensor: public Sensor {
  public:
    using Sensor::Sensor;
    TouchSensor(int pinIn, int channelIn);

    int measureValue(void);
    void measureAndSetTone(void);

    i2ctouchsensor touchsensor;
    long lastTimeValueChanged;
};

#endif //_TOUCHSENSOR_HPP_
