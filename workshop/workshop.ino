
#include "DigitalSensor.hpp"
#include "AnalogSensor.hpp"
#include "TouchSensor.hpp"
#include "UltrasonicRanger.hpp"

#define MAX_NUMBER_OF_SENSORS 32

static Sensor* listOfSensors[MAX_NUMBER_OF_SENSORS];
static int listSize = 0;

void insertSensor(Sensor* newSensor)
{
  if (listSize != MAX_NUMBER_OF_SENSORS)
  {
    listOfSensors[listSize] = newSensor;
    listSize++;
  }
}

void setup()
{
  Serial.begin(9600);
  /////////////////////////////////////
  // DO NOT MODIFY CODE ABOVE THIS LINE
  /////////////////////////////////////

//  DigitalSensor(pin, channel, note)
  //insertSensor(new DigitalSensor(3, 1, 40));  // button
 // insertSensor(new DigitalSensor(4, 1, 50));  // button

//  AnalogSensor(pin, channel, maxValue)
  insertSensor(new AnalogSensor(3, 2, 690));  //rotary
  
 // insertSensor(new AnalogSensor(1, 3, 500));  //light

//  TouchSensor(channel)
 // insertSensor(new TouchSensor(5));

//  UltrasonicRanger(pin, channel)
 // insertSensor(new UltrasonicRanger(8, 6));
  /////////////////////////////////////
  // DO NOT MODIFY CODE BELOW THIS LINE
  /////////////////////////////////////
}

void loop()
{
  for (int i = 0 ; i < listSize ; i++)
  {
    listOfSensors[i]->measureAndSetTone();
  }
  delay(10);
}





