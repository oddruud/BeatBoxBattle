#include "UltrasonicRanger.hpp"

UltrasonicRanger::UltrasonicRanger(int pinIn, int channelIn)
  : AnalogSensor(pinIn, channelIn)
{
  usSensor = new UltrasonicSensor(pin);
}

int UltrasonicRanger::measureValue(void)
{
  int reading = usSensor->measure();

  return filterValue(reading);
}

