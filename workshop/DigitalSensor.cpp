#include "DigitalSensor.hpp"

#define TIME_BETWEEN_CHANGES 10

DigitalSensor::DigitalSensor(int pinIn, int channelIn)
  : DigitalSensor(pinIn, channelIn, 60)
{}

DigitalSensor::DigitalSensor(int pinIn, int channelIn, int toneIn)
  : Sensor(pinIn, channelIn), tone(toneIn)
{
  pinMode(pin, INPUT);
  lastTimeValueChanged = millis();
}

int DigitalSensor::measureValue(void) {
  int retVal = 0;

  if ( (millis() - lastTimeValueChanged) > TIME_BETWEEN_CHANGES)
  {
    if (digitalRead(pin) )
    {
      retVal = tone;
    }
    lastTimeValueChanged = millis();
  }

  return retVal;
}
