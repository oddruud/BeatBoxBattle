#include "Sensor.hpp"

#ifndef _ANALOGSENSOR_HPP_
#define _ANALOGSENSOR_HPP_

#define SMOOTHING_BUFFER 2

class AnalogSensor: public Sensor {
  public:
    using Sensor::Sensor;
    AnalogSensor(int pinIn, int channelIn);
    AnalogSensor(int pinIn, int channelIn, int maxValueIn);

    int measureValue(void);
    void setMaxValue(int newMaxValue);
    void init(void);
    int filterValue(int);

    int maxValue;
    int filterBuffer;
};

#endif // _ANALOGSENSOR_HPP_
