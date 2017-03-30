/*
 * PIR sensor tester
 */

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
int ledPin = 13;                // choose the pin for the LED
int inputPin = 7;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
 
void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Gerald");
  
  Serial.begin(9600);
}
 
void loop(){
  val = digitalRead(inputPin);  // read input value
  lcd.setCursor(0, 1);
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      // print the number of seconds since reset:
      lcd.print("Motion detected");
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
      lcd.print("Motion ended!");
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}
