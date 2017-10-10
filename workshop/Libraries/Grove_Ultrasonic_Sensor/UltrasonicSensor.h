// +--------------+
// | ADE Workshop |
// +--------------+

#include "Arduino.h"

class UltrasonicSensor{
  public:
    // Constructor
    UltrasonicSensor(int pin);

    // Trigger function
    void trigger();
    // Response function
    int catchEcho();

    // just measure distance
    int measure();
    
  private:
    int pingPin = 0;
};

