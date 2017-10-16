#include <Wire.h> // include I2C library
#include <i2c_touch_sensor.h>
#include "DigitalSensor.hpp"
#include "AnalogSensor.hpp"

#define MAX_NUMBER_OF_SENSORS 32

byte noteON = 144;//note on command
unsigned long debounceDelay = 10;    // the debounce time; increase if the output flickers
unsigned long debounceDelayAnalog = 10;    // the debounce time; increase if the output flickers

i2ctouchsensor touchsensor; // keep track of 4 pads' states
long previousMillis = 0;
long interval = 100;

Sensor* listOfSensors[MAX_NUMBER_OF_SENSORS];
int listSize = 0;

void insertSensor(Sensor* newSensor) {
  newSensor->init();
  listOfSensors[listSize] = newSensor;
  listSize++;
}

void setup() {
Serial.begin(9600);

  insertSensor(new DigitalSensor(3,1));
  insertSensor(new AnalogSensor(0,2));

    //Wire.begin(); // needed by the GroveMultiTouch lib
    //touchsensor.initialize(); // initialize the feelers     // initialize the containers
    
    
    Serial.println("Setup done");
}

void loop() {

  //readI2CSensor();

  for(int i = 0 ; i < listSize ; i++)
  {
    int value = listOfSensors[i]->measureValue();

    listOfSensors[i]->setTone(value);
  }

  delay(100);
}




void readI2CSensor(void) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > interval)
  {
    previousMillis = currentMillis;
    touchsensor.getTouchState();
  }

  for (int i = 0; i < 4; i++)
  {
    if (touchsensor.touched & (1 << i))
    {
      //todo fix this :)
      //MIDImessage(noteON + i + 12, 60, 100);
    }
  }
}


