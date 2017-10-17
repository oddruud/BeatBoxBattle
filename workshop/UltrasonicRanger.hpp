#ifndef _ULTRASONICRANGER_HPP_
#define _ULTRASONICRANGER_HPP_

#include "AnalogSensor.hpp"
#include "UltrasonicSensor.h"

class UltrasonicRanger: public AnalogSensor
{
  public:
    using AnalogSensor::AnalogSensor;
    UltrasonicRanger(int pinIn, int channelIn);

    int measureValue(void);       // Overloaded funtion to measure the values of the ultrasonic ranger

    UltrasonicSensor* usSensor;   // Object of the ultrasonic class (3rd party), used to calculate the output of the ultrasonic sensor
};

#endif // _ULTRASONICRANGER_HPP_
