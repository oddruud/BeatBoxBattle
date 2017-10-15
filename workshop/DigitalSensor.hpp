#include "Sensor.hpp"

class DigitalSensor: public Sensor {

  using Sensor::Sensor;
  
  public:
  void init(void);
  int measureValue(void);
  
};
