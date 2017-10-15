#include "Sensor.hpp"

#define SMOOTHING_BUFFER 3

class AnalogSensor: public Sensor {

  using Sensor::Sensor;
  
  public:
  int measureValue(void);
  void setMaxValue(int newMaxValue);
  void init(void);

  private:
  int maxValue;
};
