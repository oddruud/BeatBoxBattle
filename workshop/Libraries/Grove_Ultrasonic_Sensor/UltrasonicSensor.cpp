#include "Arduino.h"
#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(int pin){
  this->pingPin = pin;
}

void UltrasonicSensor::trigger(){
  // Trigger the ultrasonic sensor with a 5us pulse
  // Set pin as output for the trigger signal
  pinMode(this->pingPin, OUTPUT);
  // Generate 5us pulse
  digitalWrite(this->pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(this->pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(this->pingPin, LOW);
}

float UltrasonicSensor::catchEcho(){
  // Catch the echo of the ultrasonic sensor
  // Switch pin back to input
  pinMode(this->pingPin, INPUT);

  // Measure the time between the trigger and the echo
  long us = pulseIn(this->pingPin, HIGH);

  // Speed of sound = 343m/s -> 29.15us per cm
  // Sound travels towards an object, bounces off and travels back. So the time measured is the 
  // distance time 2. So devide by 2 (multiply by 0.5 for faster processing)
  return us / 29.15 * 0.5;
}

