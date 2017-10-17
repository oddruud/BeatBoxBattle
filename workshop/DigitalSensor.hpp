#include "Sensor.hpp"

#ifndef _DIGITALSENSOR_HPP_
#define _DIGITALSENSOR_HPP_

class DigitalSensor: public Sensor
{
  public:
    using Sensor::Sensor;
    DigitalSensor(int pinIn, int channelIn);
    DigitalSensor(int pinIn, int channelIn, int toneIn);

    int measureValue(void);     // Overloaded funtion to measure the value of a digital sensor

    long lastTimeValueChanged;  // Timestamp of the last time the output value of the digital sensor changed, used to limit the number of changes (acts as a rudementary filter)
    int tone;                   // Value of the tone to play when the digital sensor is triggered, can be used to combine multiple tones on a single MIDI channel
};

#endif // _DIGITALSENSOR_HPP_
