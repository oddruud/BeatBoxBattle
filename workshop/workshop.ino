#include <Wire.h> // include I2C library
#include <i2c_touch_sensor.h>

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

void setup() {
  pinMode(d3, INPUT);
  pinMode(d4, INPUT);

  Wire.begin(); // needed by the GroveMultiTouch lib
  touchsensor.initialize(); // initialize the feelers     // initialize the containers

  Serial.begin(9600);
}

#define N_DIGITAL_PINS 8

int lastValuesD[N_DIGITAL_PINS] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
int currentValuesD[N_DIGITAL_PINS];
int lastDebounceTimeD[N_DIGITAL_PINS];

byte lastAnalogValue[] = {0,0,0,0};
byte currentValue[] = {0,0,0,0};
unsigned long lastDebounceTime[] = {0,0,0,0};

void setup() {
    pinMode(d3, INPUT);
    pinMode(d4, INPUT);

    lastAnalogValue[0] = map(analogRead(a0), 0, 1023, 0, 127);
    lastAnalogValue[1] = map(analogRead(a1), 0, 900, 0, 127);

    Serial.begin(9600);
}

void readAnalog(byte port) {
  int reading = analogRead(port);
  byte mappedValue = map(reading, 0, 1023, 0, 127); //map value to 127 - 0

  if (mappedValue != lastAnalogValue[port]) {
    // reset the debouncing timer
    lastDebounceTime[port] = millis();
  }

  if ((millis() - lastDebounceTime[port]) > debounceDelayAnalog) {
    // if the state has changed:
    if (mappedValue != currentValue[port]) {
      currentValue[port] = mappedValue;
      if (DEBUG) {
        Serial.print("Potmeter : ");
        Serial.println(currentValue[port]);
      } else {
        MIDImessage(noteON + port + 1, currentValue[port], 100);
      }   
    }
  }
  lastAnalogValue[port] = mappedValue;
}

void readDigital(int pin, int channel) {
  int readingPin = digitalRead(pin);

  if (readingPin != lastValuesD[pin]) {
    // reset the debouncing timer
    lastDebounceTimeD[pin] = millis();
  }

  if ((millis() - lastDebounceTimeD[pin]) > debounceDelay) {
    // if the state has changed:
    if (readingPin != currentValuesD[pin]) {
      currentValuesD[pin] = readingPin;

      // only toggle the LED if the new button state is HIGH
      if (currentValuesD[pin] == HIGH) {
        if (DEBUG) {
          Serial.println("PUSHED");
        } else {
          MIDImessage(channel, 60, 100);
        }
      }
    }
  }
  lastValuesD[pin] = readingPin;
}

void readI2CSensor(void) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > interval)
  {
    previousMillis = currentMillis;
    touchsensor.getTouchState();
  }

  for (int i = 0; i < 12; i++)
  {
    if (touchsensor.touched & (1 << i))
    {
      MIDImessage(i + 12, 60, 100);
    }
  }
}

void loop() {
  readDigital(d3, 1);
  readDigital(d4, 2);

  readI2CSensor();

  readAnalog(0);
}

//send MIDI message (noteON, note 60, loudness)
void MIDImessage(byte channel, byte data1, byte data2) {
  Serial.write( ( (channel - 1) % 16) | noteON); // noteOn command is 144, least significant 4 bits select channel, so max channel is 15! -1 because the commands are 0 indexed!
  Serial.write(data1);
  Serial.write(data2);
}
