#include <Wire.h>
#include <SevenSegmentDisplay.h>
//source 7segment code: https://github.com/alikabeel/Letters-and-Numbers-Seven-Segment-Display-Library
/*
  Showing numbers, chars and phrases
                            A (segment 7, arduino pin 12)
                           ---
  F (seg[5] in this project) |   | B (segment 6, arduino pin 11)
                          |   |
                           --- G (segment 10, arduino pin 6)
  E (seg[4] in this project) |   |
                          |   | C (segment 4, arduino pin10)
                           ---  . (segment 5, arduino pin 5 )
                            D (segment 2, arduino pin9)
*/
const int arduinoID = 10;         // MOET UNIQUE ZIJN T.O.V ANDERE ARDUINOS !!!
int code = -1;
int solved = 0;
char c = '0';
SevenSegmentDisplay digit(12, 11, 10, 9, 8, 7, 6, 5, false);  //initialization 7seg display according to library prescriptions
const int button = 2;
int buttonState = -1;                    //0 == LOW, 1 == HIGH
void setup() {
  Wire.begin(arduinoID);                // join i2c bus with address #10
  Wire.onReceive(receiveEvent);         // register event
  Wire.onRequest(puzzleSolved);
  Serial.begin(115200);                 // start serial for output
  pinMode(button, INPUT); //button as input
  digit.displayDecimalPoint(false); // DP is not needed for this usecase
  code = 5;
}

void loop() {
  c = code + '0';
  buttonState = digitalRead(button); //debug
  Serial.println(buttonState); //debug
  if (code >= 0) { // do, als code ontvangen is (dus boven 0 ligt)
    digitalRead(button);
    if (buttonState == HIGH) {                                //sensor has read the buttonpress
      //unsigned long magnet_read = millis();                             //unsigned because always >= 0
      Serial.println(buttonState);
      delay(2000);
      if (buttonState == HIGH) { //make sure the sensor sees the magnet for at least 2 whole seconds before showing answer
        digit.displayCharacter(c);
        Serial.println(c);
        solved = 1;
      }
    }
    else { //buttonState == LOW
      for(int i = 0; i < 10; i++){ //show digits 1 through 10
        buttonState = digitalRead(button);
        if(buttonState == HIGH){ //break out of loop when buttonpress is detected
          break;
          }
        digit.displayCharacter(i+'0');
        delay(200);
        }
      }
    }
  }


void receiveEvent(int howMany) {
  while (1 < Wire.available()) {  // loop through all but the last
    c = Wire.read();         // receive byte as a character
    Serial.print(c);              // print the character
  }

  code = Wire.read();            // receive byte as an integer
  Serial.println(code);         // print the integer

}

void puzzleSolved() {
  Wire.write(solved);
}
