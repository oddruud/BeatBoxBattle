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
 
byte lastValueA0 = 0;
byte currentValueA0;
unsigned long lastDebounceTimeA0 = 0;  

byte lastValueA1 = 0;
byte currentValueA1;
unsigned long lastDebounceTimeA1 = 0;  

byte noteON = 144;//note on command
unsigned long debounceDelay = 10;    // the debounce time; increase if the output flickers
unsigned long debounceDelayAnalog = 10;    // the debounce time; increase if the output flickers

void setup() {
    pinMode(d3, INPUT);
    pinMode(d4, INPUT);

    lastValueA0 = map(analogRead(a0), 0, 1023, 127, 0);
    lastValueA1 = map(analogRead(a1), 0, 900, 0, 127);
    
    Serial.begin(9600);
}

#define N_DIGITAL_PINS 8

int lastValuesD[N_DIGITAL_PINS] = {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW};
int currentValuesD[N_DIGITAL_PINS];
int lastDebounceTimeD[N_DIGITAL_PINS];

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

void loop() {

/** ANALOG INPUT A0 **/

    int readingA0 = analogRead(a0);
    byte mappedValueA0 = map(readingA0, 0, 1023, 127, 0); //map value to 127 - 0

    if (mappedValueA0 != lastValueA0) {
      // reset the debouncing timer
      lastDebounceTimeA0 = millis();
    }

    if ((millis() - lastDebounceTimeA0) > debounceDelayAnalog) {  
      // if the state has changed:
      if (mappedValueA0 != currentValueA0) {
        currentValueA0 = mappedValueA0;
//        Serial.print("Potmeter : ");
//        Serial.println(currentValueA0);
        MIDImessage(noteON, currentValueA0, 100);
      }
    }

    lastValueA0 = mappedValueA0;
/** EOF A0 **/



/** ANALOG INPUT A1 **/
    int readingA1 = analogRead(a1);
    byte mappedValueA1 = map(readingA1, 0, 900, 0, 127); //map value to 127 - 0. Dark -> 0 , Light -> 127

    if (mappedValueA1 != lastValueA1) {
      // reset the debouncing timer
      lastDebounceTimeA1 = millis();
    }

    if ((millis() - lastDebounceTimeA1) > debounceDelayAnalog) {  
      // if the state has changed:
      if (mappedValueA1 != currentValueA1) {
        currentValueA1 = mappedValueA1;
//        Serial.print("Light : ");
//        Serial.println(currentValueA1);
        MIDImessage(noteON, currentValueA1, 100);
      }
    }

    lastValueA1 = mappedValueA1;
/** EOF A1 **/


    
/** DIGITAL INPUT D3 **/
  readDigital(d3, 1);
  readDigital(d4, 2);
}

//send MIDI message (noteON, note 60, loudness)
void MIDImessage(byte channel, byte data1, byte data2) {
  Serial.write( ( (channel - 1) % 16) | noteON); // noteOn command is 144, least significant 4 bits select channel, so max channel is 15! -1 because the commands are 0 indexed!
  Serial.write(data1);
  Serial.write(data2);
}
