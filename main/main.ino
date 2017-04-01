#include <LiquidCrystal.h>
#define dataPin 8
#define clockPin 9

//SWITCH
int inputPinSwitch = 7;         // the number of the input pin
int switches = LOW;      // the current state of the output pin
int readingSwitch;           // the current reading from the input pin
int previousSwitch = LOW;    // the previous reading from the input pin
// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers

//LCD
long timeOn = 0;
long durationReady = 1000;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//PIR
int inputPinPIR = 6;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int readingPIR = 0;                    // variable for reading the pin status

//7-SEGMENT
int readingSegment = 0;
int waitTime;
const byte digit[10] = //seven segment digits in bits
{
    B00111111, // 0
    B00000110, // 1
    B01011011, // 2
    B01001111, // 3
    B01100110, // 4
    B01101101, // 5
    B01111101, // 6
    B00000111, // 7
    B01111111, // 8
    B01100111, // 9
};

void setup()
{
  lcd.begin(16, 2);
  lcd.print("EBE");
  pinMode(inputPinSwitch, INPUT);
  pinMode(inputPinPIR, INPUT);
  Serial.begin(9600);
  //delay per display in ms
  waitTime = 500;
  pinMode(clockPin, OUTPUT); // make the clock pin an output
  pinMode(dataPin , OUTPUT); // make the data pin an output
  establishContact();
}

void loop()
{
  readingSwitch = digitalRead(inputPinSwitch);
  readingPIR = digitalRead(inputPinPIR);  // read input value
  
  // if the input just went from LOW and HIGH and we've waited long enough
  // to ignore any noise on the circuit, toggle the output pin and remember
  // the time
  if (readingSwitch == LOW && previousSwitch == HIGH && millis() - time > debounce) {
    if (switches == HIGH) {
      switches = LOW;
      Serial.println("OFF");
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("OFF");
    } else {
      switches = HIGH;
      Serial.println("ON");
      timeOn = millis();
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("STARTING");
    }

    time = millis();    
  }
  
  previousSwitch = readingSwitch;
  
  if (switches == HIGH && millis() - timeOn > durationReady) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("READY");
    if (readingPIR == HIGH) {            // check if the input is HIGH
      if (pirState == LOW) {
        // we have just turned on
        Serial.println("1"); //Maju
        // We only want to print on the output change, not state
        pirState = HIGH;
      }
    } else {
      if (pirState == HIGH){
        // we have just turned of
        Serial.println("0"); //Berhenti
        // We only want to print on the output change, not state
        pirState = LOW;
      }
    }
  }

  if (Serial.available()) { // If data is available to read,
    readingSegment = Serial.read(); // read it and store it in
  }
  shiftOut(dataPin, clockPin, MSBFIRST, digit[readingSegment]);
  delay(waitTime);
}

void establishContact() {
  while (Serial.available() <= 0) {
  Serial.println("A");   // send a capital A
  delay(300);
  }
}
