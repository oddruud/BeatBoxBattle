#include "Sensor.hpp"
#include <Wire.h> // include I2C library
#include <i2c_touch_sensor.h>

Sensor::Sensor(int pinIn, int channelIn)
  : pin(pinIn), channel(channelIn)
{}

void Sensor::setTone(int value)
{
 // if(value != 0)
 // {
    MIDImessage(144 + channel, max(0, min(value, 127) ), 100);
 // }
}

void Sensor::measureAndSetTone(void)
{
  int value = measureValue();

  if (value != lastValue)
  {
    setTone(value);
    lastValue = value;
  }
}

//send MIDI message (noteON, note 60, loudness)
void Sensor::MIDImessage(int cmd, int data1, int data2)
{
  ASSERT(cmd >= 144 && cmd < 160);
  ASSERT(data1 >= 0 && data1 < 128);

#if DEBUG
  Serial.print("\nch: ");
  Serial.print(cmd - 144);
  Serial.print(" d1: ");
  Serial.print(data1);
#else
  Serial.write(cmd); // noteOn command is 144, least significant 4 bits select channel, so max channel is 15! -1 because the commands are 0 indexed!
  Serial.write(data1);
  Serial.write(data2);
#endif
}

void sensorAssert(int check, const char* checkInString, const char* filename, int lineNumber)
{
  while (!check)
  {
    Serial.print("Assertion failed!\n");
    Serial.print(checkInString);
    Serial.print("\nFile: ");
    Serial.print(filename);
    Serial.print("\nLine: ");
    Serial.print(lineNumber);
    Serial.print("\n");
    delay(5000);
  }
}

