
#include "DigitalSensor.hpp"
#include "AnalogSensor.hpp"
#include "TouchSensor.hpp"
#include "UltrasonicRanger.hpp"
#include <Adafruit_NeoPixel.h>

#define MAX_NUMBER_OF_SENSORS 32

#define LEDPIN 3 
#define LEDS 39

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS, LEDPIN, NEO_GRB + NEO_KHZ800);

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

   strip.begin();
     // Initialize all pixels to 'off'
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(253, 200, 10));
    }
    strip.show();

//  DigitalSensor(pin, channel, note)
  insertSensor(new DigitalSensor(4, 1, 50));  // button

//  AnalogSensor(pin, channel, maxValue)
  insertSensor(new AnalogSensor(0, 2, 690));  //rotary

//  TouchSensor(channel)
  insertSensor(new TouchSensor(5));

//  UltrasonicRanger(pin, channel)
  insertSensor(new UltrasonicRanger(8, 6));
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





