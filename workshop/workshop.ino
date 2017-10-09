const int a0 = A0; //rotary (map value 0-1023)
const int a1 = A1; //light (map value 0-900)
const int a2 = A2;
const int a3 = A3;

const int d3 = 3; //button
const int d4 = 4; //touch
const int d5 = 5; 


byte lastValueA0 = 0;
byte currentValueA0;
unsigned long lastDebounceTimeA0 = 0;  

byte lastValueA1 = 0;
byte currentValueA1;
unsigned long lastDebounceTimeA1 = 0;  

int currentValueD3;
int lastValueD3 = LOW;
unsigned long lastDebounceTimeD3 = 0;  // the last time the output pin was toggled

int currentValueD4;
int lastValueD4 = LOW;
unsigned long lastDebounceTimeD4 = 0;  

int currentValueD5;
int lastValueD5 = LOW;
unsigned long lastDebounceTimeD5 = 0;  

byte noteON = 144;//note on command
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
unsigned long debounceDelayAnalog = 10;    // the debounce time; increase if the output flickers

void setup() {
    pinMode(d3, INPUT);
    pinMode(d4, INPUT);

    lastValueA0 = map(analogRead(a0), 0, 1023, 127, 0);
    lastValueA1 = map(analogRead(a1), 0, 900, 0, 127);
    
    Serial.begin(9600);
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
    int readingD3 = digitalRead(d3);
    
    if (readingD3 != lastValueD3) {
      // reset the debouncing timer
      lastDebounceTimeD3 = millis();
    }

    if ((millis() - lastDebounceTimeD3) > debounceDelay) {  
      // if the state has changed:
      if (readingD3 != currentValueD3) {
        currentValueD3 = readingD3;
  
        // only toggle the LED if the new button state is HIGH
        if (currentValueD3 == HIGH) {
//          Serial.println("PUSH");
          MIDImessage(noteON, 60, 100);
        }
      }
    }

    lastValueD3 = readingD3;
/** EOF D3 **/



/** DIGITAL INPUT D4 **/
    int readingD4 = digitalRead(d4);
    
    if (readingD4 != lastValueD4) {
      // reset the debouncing timer
      lastDebounceTimeD4 = millis();
    }

    if ((millis() - lastDebounceTimeD4) > debounceDelay) {  
      // if the state has changed:
      if (readingD4 != currentValueD4) {
        currentValueD4 = readingD4;
  
        // only toggle the LED if the new button state is HIGH
        if (currentValueD4 == HIGH) {
//          Serial.println("TOUCH");
          MIDImessage(noteON, 60, 100);
        }
      }
    }

    lastValueD4 = readingD4;
/** EOF D4 **/



/** DIGITAL INPUT D5 **/
    int readingD5 = digitalRead(d5);
    
    if (readingD5 != lastValueD5) {
      // reset the debouncing timer
      lastDebounceTimeD5 = millis();
    }

    if ((millis() - lastDebounceTimeD5) > debounceDelay) {  
      // if the state has changed:
      if (readingD5 != currentValueD5) {
        currentValueD5 = readingD5;
  
        // only toggle the LED if the new button state is HIGH
        if (currentValueD5 == HIGH) {
//          Serial.println("LIGHT");
          MIDImessage(noteON, 60, 100);
        }
      }
    }

    lastValueD5 = readingD5;
/** EOF D5 **/


}

//send MIDI message (noteON, note 60, loudness)
void MIDImessage(byte command, byte data1, byte data2) {
  Serial.write(command);
  Serial.write(data1);
  Serial.write(data2);
}
