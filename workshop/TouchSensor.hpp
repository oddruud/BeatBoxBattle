#include "Sensor.hpp"
#include <Wire.h> // include I2C library
#include <i2c_touch_sensor.h>

#define N_TOUCHPADS 4

class TouchSensor: public Sensor {

  using Sensor::Sensor;
  
  public:
  void init(void);
  int measureValue(void);
  void measureAndSetTone(void);

  i2ctouchsensor touchsensor;
  long lastTimeValueChanged;
};
