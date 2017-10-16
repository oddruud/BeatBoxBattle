#include "TouchSensor.hpp"

#define TIME_BETWEEN_CHANGES 10

void TouchSensor::init(void) {
  Wire.begin(); // needed by the GroveMultiTouch lib
  touchsensor.initialize();

  lastTimeValueChanged = millis();
}

int TouchSensor::measureValue(void) {
  int retVal = 0;

  if ( (millis() - lastTimeValueChanged) > TIME_BETWEEN_CHANGES)
  {
    lastTimeValueChanged = millis();
    touchsensor.getTouchState();
    retVal = touchsensor.touched;
  }
}

void TouchSensor::measureAndSetTone(void) {
  int value = measureValue();

  if (value != lastValue) {
    for (int i = 0 ; i < N_TOUCHPADS ; i++)
    {
      if (value & (1 << i))
      {
        setTone(i);
      }
    }
    lastValue = value;
  }
}

