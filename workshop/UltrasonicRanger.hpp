#ifndef _ULTRASONICRANGER_HPP_
#define _ULTRASONICRANGER_HPP_

#include "AnalogSensor.hpp"
#include "UltrasonicSensor.h"

class UltrasonicRanger: public AnalogSensor {
  public:
    using AnalogSensor::AnalogSensor;
    UltrasonicRanger(int pinIn, int channelIn);

    int measureValue(void);

    UltrasonicSensor* usSensor;
};

#endif // _ULTRASONICRANGER_HPP_
