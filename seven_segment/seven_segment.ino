#define dataPin 8
#define clockPin 9
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
  //delay per display in ms
  waitTime = 500;

  pinMode(clockPin, OUTPUT); // make the clock pin an output
  pinMode(dataPin , OUTPUT); // make the data pin an output
}

void loop(){
    // step through each digit then increment 
    // the counter by one, until nine
    for(int j=0; j<=9; j++){
        // send this binary value to the shift register
        shiftOut(dataPin, clockPin, MSBFIRST, digit[j]);
        delay(waitTime);
    }
}


