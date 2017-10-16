#include "AnalogSensor.hpp"

void AnalogSensor::init(void) {
  maxValue = 690; // Default value
}

int AnalogSensor::measureValue(void) {
  int retVal = 0;
  int reading = analogRead(pin);
  
  int filteredReading = filterValue(reading);

  retVal = map(filteredReading, 0, maxValue, 0, 127);

  return retVal;
}

int AnalogSensor::filterValue(int inputValue) {
  int filteredReading = ( (SMOOTHING_BUFFER * filterBuffer) + inputValue) / (SMOOTHING_BUFFER + 1);
  filterBuffer = filteredReading;

  return filteredReading;
}

void AnalogSensor::setMaxValue(int newMaxValue)
{
  maxValue = newMaxValue;
}

