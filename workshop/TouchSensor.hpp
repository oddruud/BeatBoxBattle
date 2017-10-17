#ifndef _TOUCHSENSOR_HPP_
#define _TOUCHSENSOR_HPP_

#include "Sensor.hpp"
#include <Wire.h> // include I2C library
#include <i2c_touch_sensor.h>

#define N_TOUCHPADS 12            // 12 instead of the real 8, because 4 pins on the I2C sensor are skipped!

class TouchSensor: public Sensor
{
  public:
    using Sensor::Sensor;
    TouchSensor(int channelIn);

    int measureValue(void);       // Overloaded funtion to measure the values of the touch sensors
    void measureAndSetTone(void); // Overloaded funtion to trigger the measure values function and trigger setTones for each touch sensor independly

    i2ctouchsensor touchsensor;   // Object of the touchsensor class (3rd party), used to read out the touch sensor
    long lastTimeValueChanged;    // Timestamp of the last time the output value of the touch sensors changed, used to limit the number of changes (acts as a rudementary filter)
};

#endif //_TOUCHSENSOR_HPP_
