#include "DigitalSensor.hpp"

#define TIME_BETWEEN_CHANGES 10

void DigitalSensor::init(void) {
  pinMode(pin, INPUT);
  lastTimeValueChanged = millis();
}

int DigitalSensor::measureValue(void) {
  int retVal = 0;

  if( (millis() - lastTimeValueChanged) > TIME_BETWEEN_CHANGES) 
  {
    retVal = digitalRead(pin);
    lastTimeValueChanged = millis();
  }
  
  return retVal;
}
