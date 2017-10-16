#include "AnalogSensor.hpp"

AnalogSensor::AnalogSensor(int pinIn, int channelIn)
  : AnalogSensor(pinIn, channelIn, 1023)
{}

AnalogSensor::AnalogSensor(int pinIn, int channelIn, int maxValueIn)
  : Sensor(pinIn, channelIn), maxValue(maxValueIn)
{}

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

