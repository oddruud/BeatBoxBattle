#ifndef _SENSOR_HPP_
#define _SENSOR_HPP_

#include "Arduino.h"

#define DEBUG 0 // Turn this to 1 to change the MIDI messages to readable ASCII output

#define ASSERT(x) sensorAssert(x, #x, __FILE__, __LINE__) // Macro function used to help debug the code

// Sensor base class, DO NOT USE DIRECTLY
class Sensor
{
  public:
    Sensor(int pinIn, int channelIn);

    virtual int measureValue(void) = 0;   // Pure virtual placeholder of function for measuring of a sensors value
    virtual void measureAndSetTone(void); // Virtual function for triggering the sensors measure function and outputting it to the setTone function

    void setTone(int value);                        // Base class function used to send a tone to the MIDI device
    void MIDImessage(int cmd, int data1, int data2);// Base class function used to format a MIDI message

    int pin;        // Pin on Arduino, can be analog or digital (or in case of touchSensor unused)
    int channel;    // MIDI channel, on which channel to transmit the tone of the sensor

    int lastValue;  // Last output value of a sensor, used to only transmit changes in values
};

void sensorAssert(int check, const char* checkInString, const char* filename, int lineNumber); // Special function used to help debug the code DO NOT USE DIRECTLY, use MACRO ABOVE

#endif // _SENSOR_HPP_
