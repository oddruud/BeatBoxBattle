#include "Sensor.hpp"

#define SMOOTHING_BUFFER 2

class AnalogSensor: public Sensor {

  using Sensor::Sensor;
  
  public:
  int measureValue(void);
  void setMaxValue(int newMaxValue);
  void init(void);
  int filterValue(int);

  private:
  int maxValue;
  int filterBuffer;
};
