#include "AnalogSensor.hpp"
#include <Wire.h> // include I2C library
#include <i2c_touch_sensor.h>

void AnalogSensor::init(void) {
  maxValue = 690; // Default value
}

int AnalogSensor::measureValue(void) {
  int retVal = 0;
  int reading = analogRead(pin);
  
  int filteredReading = ( (SMOOTHING_BUFFER * lastValue) + reading) / (SMOOTHING_BUFFER + 1);

  retVal = map(filteredReading, 0, maxValue, 0, 127);

  lastValue = filteredReading;

  return retVal;
}

void AnalogSensor::setMaxValue(int newMaxValue)
{
  maxValue = newMaxValue;
}

