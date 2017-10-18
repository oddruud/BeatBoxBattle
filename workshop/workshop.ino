
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

//Brunos switchboard:
 insertSensor(new DigitalSensor(2, 1, 40));  // light
 insertSensor(new DigitalSensor(3, 1, 50));  // light
 insertSensor(new DigitalSensor(4, 1, 60));  // light
 insertSensor(new DigitalSensor(5, 1, 70));  // light
 
//Ultrasonic RANGE (instrument slider)
 insertSensor(new UltrasonicRanger(6, 6));

//Ultrasonic RANGE (Filters)
 insertSensor(new UltrasonicRanger(7, 7));
 insertSensor(new UltrasonicRanger(7, 8));

//  DigitalSensor(pin, channel, note)
  //insertSensor(new DigitalSensor(3, 1, 40));  // button
//  insertSensor(new DigitalSensor(4, 1, 50));  // button
//  AnalogSensor(pin, channel, maxValue)
  //insertSensor(new AnalogSensor(1, 2, 690));  //rotary
 //insertSensor(new AnalogSensor(3, 3, 500));  //light
//  TouchSensor(channel)
 // insertSensor(new TouchSensor(5));
//  UltrasonicRanger(pin, channel)
 // insertSensor(new UltrasonicRanger(4, 6));



 
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





