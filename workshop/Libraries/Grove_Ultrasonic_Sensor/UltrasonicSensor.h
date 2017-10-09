// placeholder
#include "Arduino.h"


class UltrasonicSensor{
  public:
    UltrasonicSensor(int pin);
    void trigger();
    float catchEcho();
  private:
    int pingPin = 0;
};

