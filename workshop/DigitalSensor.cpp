#include "DigitalSensor.hpp"
#include <Wire.h> // include I2C library
#include <i2c_touch_sensor.h>

#define TIME_BETWEEN_CHANGES 10

void DigitalSensor::init(void) {
  pinMode(pin, INPUT);
}

int DigitalSensor::measureValue(void) {
  int retVal = 0;

  if( (millis() - lastTimeValueChanged) > TIME_BETWEEN_CHANGES) 
  {
    int readingPin = digitalRead(pin);
    // if the state has changed:
    if (readingPin != lastValue) {
     lastValue = readingPin;

      // only toggle the LED if the new button state is HIGH
      if (readingPin == HIGH) {
        retVal = 1;
      }
    }
  }
  lastTimeValueChanged = millis();

  return retVal;
}
