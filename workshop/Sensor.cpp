#include "Sensor.hpp"
#include <Wire.h> // include I2C library
#include <i2c_touch_sensor.h>

Sensor::Sensor(int pinIn, int channelIn) 
: Sensor(pinIn, channelIn, 60)
{}

Sensor::Sensor(int pinIn, int channelIn, int toneIn)
: pin(pinIn), channel(channelIn), tone(toneIn)
{
  ASSERT(pinIn < CHANNEL_MAX); 
  lastTimeValueChanged = millis();
}

void Sensor::setTone(int value) {
  MIDImessage(144 + channel, tone, 100);
}

//send MIDI message (noteON, note 60, loudness)
void Sensor::MIDImessage(int cmd, int data1, int data2) {
#ifndef DEBUG
  Serial.write(cmd); // noteOn command is 144, least significant 4 bits select channel, so max channel is 15! -1 because the commands are 0 indexed!
  Serial.write(data1);
  Serial.write(data2);
#else
  Serial.print("\nmidimsg: ");
  Serial.print(cmd); // noteOn command is 144, least significant 4 bits select channel, so max channel is 15! -1 because the commands are 0 indexed!
  Serial.print(data1);
  Serial.print(data2);
#endif
}

void Sensor::sensorAssert(int check, char* assertString, char* filename, int lineNumber) {
  while(!check) {
    Serial.print("Assertion failed!\n");
    Serial.print(assertString);
    Serial.print("\nFile: ");
    Serial.print(filename);
    Serial.print("\nLine: ");
    Serial.print(lineNumber);
    Serial.print("\n");
    delay(5000);
  }
}

