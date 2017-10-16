
#include "DigitalSensor.hpp"
#include "AnalogSensor.hpp"
#include "TouchSensor.hpp"

#define MAX_NUMBER_OF_SENSORS 32

Sensor* listOfSensors[MAX_NUMBER_OF_SENSORS];
int listSize = 0;

void insertSensor(Sensor* newSensor) {
  if (listSize != MAX_NUMBER_OF_SENSORS) {
    newSensor->init();
    listOfSensors[listSize] = newSensor;
    listSize++;
  }
}

void setup() {
  Serial.begin(9600);

  insertSensor(new DigitalSensor(3, 1));
  insertSensor(new AnalogSensor(0, 2));
  insertSensor(new TouchSensor(0, 3));

  Serial.println("Setup done");
}

void loop() {

  for (int i = 0 ; i < listSize ; i++)
  {
    listOfSensors[i]->measureAndSetTone();
  }

  delay(100);
}





