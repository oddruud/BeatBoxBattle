#include "Sensor.hpp"

#ifndef _DIGITALSENSOR_HPP_
#define _DIGITALSENSOR_HPP_

class DigitalSensor: public Sensor {
  public:
    using Sensor::Sensor;
    DigitalSensor(int pinIn, int channelIn);
    DigitalSensor(int pinIn, int channelIn, int toneIn);

    void init(void);
    int measureValue(void);

    long lastTimeValueChanged;
    int tone;                   // What tone to play
};

#endif // _DIGITALSENSOR_HPP_
