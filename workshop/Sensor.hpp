#ifndef _SENSOR_HPP_
#define _SENSOR_HPP_

#include "Arduino.h"

#define DEBUG 1

#define ASSERT(x) sensorAssert(x, #x, __FILE__, __LINE__)

class Sensor {
  public:
    Sensor(int pinIn, int channelIn);

    virtual int measureValue(void) = 0;

    virtual void measureAndSetTone(void);

    void setTone(int value);
    void MIDImessage(int cmd, int data1, int data2);

    int pin;      // Pin on Arduino, can be analog or digital (or in case of touchSensor obsolete)
    int channel;  // Midi channel, on which channel to transmit the tone of the sensor

    int lastValue;
};

void sensorAssert(int check, const char* checkInString, const char* filename, int lineNumber);

#endif // _SENSOR_HPP_
