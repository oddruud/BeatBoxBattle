/* GroveI2CTouchTest.pde - Sample code for the SeeedStudio Grove I2C Touch Sensor
http://seeedstudio.com/wiki/index.php?title=Twig_-_I2C_Touch_Sensor_v0.93b  
Prerequisite: A modification of the Grove I2C Touch sensor is needed Solder a pin to
the INT terminal in the I2C sensor to connect it to one pin in Arduino  Created by
Wendell A. Capili, August 27, 2011. http://wendellinfinity.wordpress.com  
Released into the public domain.*/

#include <Wire.h> // include I2C library
#include <i2c_touch_sensor.h>

i2ctouchsensor touchsensor; // keep track of 4 pads' states
long previousMillis = 0;
long interval = 100;
void setup() 
  {    
    Serial.begin(9600); // for debugging   
    Wire.begin(); // needed by the GroveMultiTouch lib     
    touchsensor.initialize(); // initialize the feelers     // initialize the containers   
  
  }

  
void loop()
{     
 readI2CSensor();

}  

void readI2CSensor(void)
{
 
   unsigned long currentMillis = millis();
 if(currentMillis - previousMillis > interval)
  {
    previousMillis = currentMillis;
    touchsensor.getTouchState();
  }
  
   for (int i=0;i<12;i++)
 {
    if (touchsensor.touched&(1<<i))
    { 
        
          MIDImessage(i+12, 60, 100);
       }
 }
}




//send MIDI message (noteON, note 60, loudness)
void MIDImessage(byte command, byte data1, byte data2) {
  Serial.write(command | 144);
  Serial.write(data1);
  Serial.write(data2);
}
