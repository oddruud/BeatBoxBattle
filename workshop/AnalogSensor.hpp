#include "Sensor.hpp"

#ifndef _ANALOGSENSOR_HPP_
#define _ANALOGSENSOR_HPP_

#define SMOOTHING_BUFFER 8

class AnalogSensor: public Sensor
{
  public:
    using Sensor::Sensor;
    AnalogSensor(int pinIn, int channelIn);
    AnalogSensor(int pinIn, int channelIn, int maxValueIn);

    int measureValue(void); // Overloaded function to measure the value of an analog sensor
    int filterValue(int);   // Function to filter the input values of an analog sensor

    int maxValue;     // Maximum expected output value of the sensor, it's output will be remapped expecting this value as its max
    int filterBuffer; // Value holding the last filtered values
};

#endif // _ANALOGSENSOR_HPP_
