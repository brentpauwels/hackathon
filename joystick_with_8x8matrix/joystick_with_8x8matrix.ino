#include "LedControl.h"
//source LedControl: http://wayoda.github.io/LedControl/
//source joystick: https://arduinogetstarted.com/tutorials/arduino-joystick
#include <Wire.h>

const int arduinoID = 11;         // MOET UNIQUE ZIJN T.O.V ANDERE ARDUINOS !!!
int code = -1;
int solved = 1;                  // 1 == solved, false != solved
bool Digit[8][8];
LedControl lc = LedControl(12, 11, 10, 1); //12 = DataIn, 11 = CLK, 10 = LOAD

#define X_PIN  A0 // joystick X_PIN analog pin
#define Y_PIN  A1 // joystick Y_PIN analog pin 
int xValue = 0; // xCo storage, default for x is  513, full left = 0, right = 1023
int yValue = 0; // yCo storage default for y is 521, full up = 0, down = 1023
unsigned long delaytime = 1010; //startdelay

void setup() {
  lc.shutdown(0, false); //wakes up the 7219 IC (default is off for power saving)
  lc.setIntensity(0, 15); //set leds intensity between 0 and 15
  lc.clearDisplay(0); // turn off entire display

  Wire.begin(arduinoID);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(puzzleSolved);
  Serial.begin(115200);           // start serial for output
}

void loop() {
  if (code >= 0) { // execute puzzle when program has gotten its code
    xValue = analogRead(X_PIN); //get initial xValue
    yValue = analogRead(Y_PIN); //get intial yValue
    if (yValue > 521) { //joystick is pointing down
      for (int row = 7; row >= 0; row--) { //iterate over 8 rows en 8 cols from right down to left up
        for (int col = 7; col >= 0; col--) {
          lc.setLed(0, row, col, Digit[row][col]); //setLed method: 0 = address (only for multiple displays), row, col, true/1 = led on and false/0 = led off
          delay(delaytime);
          lc.clearDisplay(0);
          int yValue2 = analogRead(Y_PIN);
          if ( yValue2 < yValue - 10 || yValue2 > yValue + 10 ) { //check if yValue changed, margin for hysteresis
            yValue = yValue2;
            break;
          }
          xValue = analogRead(X_PIN);
          if (xValue > 700 && delaytime > 100 ) { //joystick pointing right, margin for hysteresis
            delaytime -= 100;
          }
          else if (xValue < 300 && delaytime <= 1000) { //joystick pointing left, margin for hysteresis
            delaytime += 100;
          }
        }
      }
    }

    //case joystick mid or pointing up (DEFAULT)
    else {
      for (int row = 0; row < 8; row++) { //iterate over 8 rows en 8 cols from left up to right down
        for (int col = 0; col < 8; col++) {
          lc.setLed(0, row, col, true); //setLed method: 0 = address (only for multiple displays), row, col, true/1 = led on and false/0 = led off
          delay(delaytime);
          lc.clearDisplay(0);
          int yValue2 = analogRead(Y_PIN);
          if (yValue2 < yValue - 10 || yValue2 > yValue + 10 ) { //check if yValue changed, margin for hysteresis
            yValue = yValue2;
            break;
          }
          xValue = analogRead(X_PIN);
          if (xValue > 700 && delaytime > 100 ) { //joystick pointing right, room for hysteresis
            delaytime -= 100;
          }
          else if (xValue < 300 && delaytime <= 200) { //joystick pointing left, margin for hysteresis
            delaytime += 100;
          }
        }
      }
    }
  }
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  code = Wire.read();    // receive byte as an integer
  Serial.println(code);         // print the integer
  switch (code) {
    default: //heart
      Digit[8][8] = { 
        {false, true, true, false, false, true, true, false},
        {true, true, true, true, true, true, true, true},
        {true, true, true, true, true, true, true, true},
        {true, true, true, true, true, true, true, true},
        {true, true, true, true, true, true, true, true},
        {false, true, true, true, true, true, true, false},
        {false, false, true, true, true, true, false, false},
        {false, false, false, true, true, false, false, false}
      };
      break;

    case 1:
      Digit[8][8] = { 
        {false, false, false, true, false, false, false, false},
        {false, false, true, true, false, false, false, false},
        {false, false, false, true, false, false, false, false},
        {false, false, false, true, false, false, false, false},
        {false, false, false, true, false, false, false, false},
        {false, false, false, true, false, false, false, false},
        {false, false, false, true, false, false, false, false},
        {false, false, true, true, true, false, false, false}
      };
      break;

    case 2: 
      Digit[8][8] = {
        {false, false, true, true, true, false, false, false},
        {false, true, false, false, false, true, false, false},
        {false, false, false, false, false, true, false, false},
        {false, false, false, false, false, true, false, false},
        {false, false, false, false, true, false, false, false},
        {false, false, false, true, false, false, false, false},
        {false, false, true, false, false, false, false, false},
        {false, true, true, true, true, true, false, false}
      };
      break;

    case 3:
      Digit[8][8] = {
        {false, false, true, true, true, false, false, false},
        {false, true, false, false, false, true, false, false},
        {false, false, false, false, false, true, false, false},
        {false, false, false, true, true, false, false, false},
        {false, false, false, false, false, true, false, false},
        {false, false, false, false, false, true, false, false},
        {false, true, false, false, false, true, false, false},
        {false, false, true, true, true, false, false, false}
      };
      break;

    case 4:
      Digit[8][8] =  {
        {false, false, false, false, false, false, false, false},
        {false, false, false, false, true, true, false, false},
        {false, false, false, true, false, true, false, false},
        {false, false, true, false, false, true, false, false},
        {false, true, false, false, false, true, false, false},
        {false, true, true, true, true, true, false, false},
        {false, false, false, false, false, true, false, false},
        {false, false, false, false, false, true, false, false}
      };
      break;

    case 5:
      Digit[8][8] = {
        {false, true, true, true, true, true, false, false},
        {false, true, false, false, false, false, false, false},
        {false, true, false, false, false, false, false, false},
        {false, true, true, true, true, false, false, false},
        {false, false, false, false, false, true, false, false},
        {false, false, false, false, false, true, false, false},
        {false, true, false, false, false, true, false, false},
        {false, false, true, true, true, false, false, false}
      };
      break;

    case 6:
      Digit[8][8] = {
        {false, false, true, true, true, false, false, false},
        {false, true, false, false, false, true, false, false},
        {false, true, false, false, false, false, false, false},
        {false, true, true, true, true, false, false, false},
        {false, true, false, false, false, true, false, false},
        {false, true, false, false, false, true, false, false},
        {false, true, false, false, false, true, false, false},
        {false, false, true, true, true, false, false, false}
      };
      break;

    case 7:
      Digit[8][8] = {
        {false, true, true, true, true, true, false, false},
        {false, false, false, false, false, true, false, false},
        {false, false, false, false, false, true, false, false},
        {false, false, false, false, true, false, false, false},
        {false, false, false, true, false, false, false, false},
        {false, false, true, false, false, false, false, false},
        {false, false, true, false, false, false, false, false},
        {false, false, true, false, false, false, false, false}
      };
      break;

    case 8:
      Digit[8][8] = {
        {false, false, true, true, true, false, false, false},
        {false, true, false, false, false, true, false, false},
        {false, true, false, false, false, true, false, false},
        {false, false, true, true, true, false, false, false},
        {false, true, false, false, false, true, false, false},
        {false, true, false, false, false, true, false, false},
        {false, true, false, false, false, true, false, false},
        {false, false, true, true, true, false, false, false}
      };
      break;

    case 9:
      Digit[8][8] = {
        {false, false, true, true, true, false, false, false},
        {false, true, false, false, false, true, false, false},
        {false, true, false, false, false, true, false, false},
        {false, true, false, false, false, true, false, false},
        {false, false, true, true, true, true, false, false},
        {false, false, false, false, false, true, false, false},
        {false, true, false, false, false, true, false, false},
        {false, false, true, true, true, false, false, false}
      };
      break;

    case 0:
      Digit[8][8] = {
        {false, false, true, true, true, false, false, false},
        {false, true, false, false, false, true, false, false},
        {false, true, false, false, false, true, false, false},
        {false, true, false, false, false, true, false, false},
        {false, true, false, false, false, true, false, false},
        {false, true, false, false, false, true, false, false},
        {false, true, false, false, false, true, false, false},
        {false, false, true, true, true, false, false, false}
      };
      break;
  }
}

void puzzleSolved() {
  Wire.write(solved);
}
