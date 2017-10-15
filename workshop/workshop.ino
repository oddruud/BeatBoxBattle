#include <Wire.h> // include I2C library
#include <i2c_touch_sensor.h>
#include "DigitalSensor.hpp"
#include "AnalogSensor.hpp"

#define MAX_NUMBER_OF_SENSORS 32

#define a0 A0 //rotary (map value 0-1023)
#define a1 A1 //light (map value 0-900)
#define a2 A2
#define a3 A3

#define d2 2
#define d3 3
#define d4 4
#define d5 5
#define d6 6
#define d7 7

#define DEBUG 0

byte noteON = 144;//note on command
unsigned long debounceDelay = 10;    // the debounce time; increase if the output flickers
unsigned long debounceDelayAnalog = 10;    // the debounce time; increase if the output flickers

i2ctouchsensor touchsensor; // keep track of 4 pads' states
long previousMillis = 0;
long interval = 100;

Sensor* listOfSensors[MAX_NUMBER_OF_SENSORS];
int listSize = 0;

void insertSensor(Sensor* newSensor) {
  listOfSensors[listSize] = newSensor;
  listSize++;
}

void setup() {

  insertSensor(new DigitalSensor(3,1));
  insertSensor(new AnalogSensor(0,2));

    //Wire.begin(); // needed by the GroveMultiTouch lib
    //touchsensor.initialize(); // initialize the feelers     // initialize the containers
    
    Serial.begin(9600);
    Serial.println("Setup done");
}

void loop() {

  //readI2CSensor();


  for(int i = 0 ; i < listSize ; i++)
  {
    int value = listOfSensors[i]->measureValue();

    listOfSensors[i]->setTone(value);
  }

  delay(200);
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
      MIDImessage(noteON + i + 12, 60, 100);
    }
  }
}

//send MIDI message (noteON, note 60, loudness)
void MIDImessage(byte cmd, byte data1, byte data2) {
  Serial.write(cmd); // noteOn command is 144, least significant 4 bits select channel, so max channel is 15! -1 because the commands are 0 indexed!
  Serial.write(data1);
  Serial.write(data2);
}
