#include "LedControl.h"
//source LedControl: http://wayoda.github.io/LedControl/
//source joystick: https://arduinogetstarted.com/tutorials/arduino-joystick
#include <Wire.h>

const int arduinoID = 11;         // MOET UNIQUE ZIJN T.O.V ANDERE ARDUINOS !!!
int code = -1;
int solved = 1;                  // 1 == solved, false != solved
bool Digit[8][8];
LedControl lc = LedControl(4, 3, 2, 1); //4 = DataIn, 3 = CLK, 2 = LOAD

#define X_PIN  A0 // joystick X_PIN analog pin
#define Y_PIN  A1 // joystick Y_PIN analog pin 
int xValue = 0; // xCo storage, default for x is  513, full left = 0, right = 1023
int yValue = 0; // yCo storage default for y is 521, full up = 0, down = 1023
unsigned int delaytime = 1001; //startdelay
unsigned long max_reached = -1;
bool maximum = false;

void setup() {
  lc.shutdown(0, false); //wakes up the 7219 IC (default is off for power saving)
  lc.setIntensity(0, 8); //set leds intensity between 0 and 15
  lc.clearDisplay(0); // turn off entire display
  Wire.begin(arduinoID);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(puzzleSolved);
  Serial.begin(115200); // start serial for output
  int code = 9;
  switch (code) {
    default: //heart
      Digit[0][0] = false;
      Digit[0][1] = true;
      Digit[0][2] = true;
      Digit[0][3] = false;
      Digit[0][4] = false;
      Digit[0][5] = true;
      Digit[0][6] = true;
      Digit[0][7] = false;

      Digit[1][0] = true;
      Digit[1][1] = true;
      Digit[1][2] = true;
      Digit[1][3] = true;
      Digit[1][4] = true;
      Digit[1][5] = true;
      Digit[1][6] = true;
      Digit[1][7] = true;
      
      Digit[2][0] = true;
      Digit[2][1] = true;
      Digit[2][2] = true;
      Digit[2][3] = true;
      Digit[2][4] = true;
      Digit[2][5] = true;
      Digit[2][6] = true;
      Digit[2][7] = true;
            
      Digit[3][0] = true;
      Digit[3][1] = true;
      Digit[3][2] = true;
      Digit[3][3] = true;
      Digit[3][4] = true;
      Digit[3][5] = true;
      Digit[3][6] = true;
      Digit[3][7] = true;

      Digit[4][0] = true;
      Digit[4][1] = true;
      Digit[4][2] = true;
      Digit[4][3] = true;
      Digit[4][4] = true;
      Digit[4][5] = true;
      Digit[4][6] = true;
      Digit[4][7] = true;

      Digit[5][0] = false;
      Digit[5][1] = true;
      Digit[5][2] = true;
      Digit[5][3] = true;
      Digit[5][4] = true;
      Digit[5][5] = true;
      Digit[5][6] = true;
      Digit[5][7] = false;

      Digit[6][0] = false;
      Digit[6][1] = false;
      Digit[6][2] = true;
      Digit[6][3] = true;
      Digit[6][4] = true;
      Digit[6][5] = true;
      Digit[6][6] = false;
      Digit[6][7] = false;

      Digit[7][0] = false;
      Digit[7][1] = false;
      Digit[7][2] = false;
      Digit[7][3] = true;
      Digit[7][4] = true;
      Digit[7][5] = false;
      Digit[7][6] = false;
      Digit[7][7] = false;
      break;

    case 1:
      Digit[0][0] = false;
      Digit[0][1] = false;
      Digit[0][2] = false;
      Digit[0][3] = true;
      Digit[0][4] = false;
      Digit[0][5] = false;
      Digit[0][6] = false;
      Digit[0][7] = false;

      Digit[1][0] = false;
      Digit[1][1] = false;
      Digit[1][2] = true;
      Digit[1][3] = true;
      Digit[1][4] = false;
      Digit[1][5] = false;
      Digit[1][6] = false;
      Digit[1][7] = false;

      Digit[2][0] = false;
      Digit[2][1] = false;
      Digit[2][2] = false;
      Digit[2][3] = true;
      Digit[2][4] = false;
      Digit[2][5] = false;
      Digit[2][6] = false;
      Digit[2][7] = false;

      Digit[3][0] = false;
      Digit[3][1] = false;
      Digit[3][2] = false;
      Digit[3][3] = true;
      Digit[3][4] = false;
      Digit[3][5] = false;
      Digit[3][6] = false;
      Digit[3][7] = false;

      Digit[4][0] = false;
      Digit[4][1] = false;
      Digit[4][2] = false;
      Digit[4][3] = true;
      Digit[4][4] = false;
      Digit[4][5] = false;
      Digit[4][6] = false;
      Digit[4][7] = false;

      Digit[5][0] = false;
      Digit[5][1] = false;
      Digit[5][2] = false;
      Digit[5][3] = true;
      Digit[5][4] = false;
      Digit[5][5] = false;
      Digit[5][6] = false;
      Digit[5][7] = false;

      Digit[6][0] = false;
      Digit[6][1] = false;
      Digit[6][2] = false;
      Digit[6][3] = true;
      Digit[6][4] = false;
      Digit[6][5] = false;
      Digit[6][6] = false;
      Digit[6][7] = false;

      Digit[7][0] = false;
      Digit[7][1] = false;
      Digit[7][2] = true;
      Digit[7][3] = true;
      Digit[7][4] = true;
      Digit[7][5] = false;
      Digit[7][6] = false;
      Digit[7][7] = false;
      break;

    case 2:
      Digit[0][0] = false;
      Digit[0][1] = false;
      Digit[0][2] = true;
      Digit[0][3] = true;
      Digit[0][4] = true;
      Digit[0][5] = false;
      Digit[0][6] = false;
      Digit[0][7] = false;

      Digit[1][0] = false;
      Digit[1][1] = true;
      Digit[1][2] = false;
      Digit[1][3] = false;
      Digit[1][4] = false;
      Digit[1][5] = true;
      Digit[1][6] = false;
      Digit[1][7] = false;

      Digit[2][0] = false;
      Digit[2][1] = false;
      Digit[2][2] = false;
      Digit[2][3] = false;
      Digit[2][4] = false;
      Digit[2][5] = true;
      Digit[2][6] = false;
      Digit[2][7] = false;

      Digit[3][0] = false;
      Digit[3][1] = false;
      Digit[3][2] = false;
      Digit[3][3] = false;
      Digit[3][4] = false;
      Digit[3][5] = true;
      Digit[3][6] = false;
      Digit[3][7] = false;

      Digit[4][0] = false;
      Digit[4][1] = false;
      Digit[4][2] = false;
      Digit[4][3] = false;
      Digit[4][4] = true;
      Digit[4][5] = false;
      Digit[4][6] = false;
      Digit[4][7] = false;

      Digit[5][0] = false;
      Digit[5][1] = false;
      Digit[5][2] = false;
      Digit[5][3] = true;
      Digit[5][4] = false;
      Digit[5][5] = false;
      Digit[5][6] = false;
      Digit[5][7] = false;

      Digit[6][0] = false;
      Digit[6][1] = false;
      Digit[6][2] = true;
      Digit[6][3] = false;
      Digit[6][4] = false;
      Digit[6][5] = false;
      Digit[6][6] = false;
      Digit[6][7] = false;

      Digit[7][0] = false;
      Digit[7][1] = true;
      Digit[7][2] = true;
      Digit[7][3] = true;
      Digit[7][4] = true;
      Digit[7][5] = true;
      Digit[7][6] = false;
      Digit[7][7] = false;
      break;

    case 3:
      Digit[0][0] = false;
      Digit[0][1] = false;
      Digit[0][2] = true;
      Digit[0][3] = true;
      Digit[0][4] = true;
      Digit[0][5] = false;
      Digit[0][6] = false;
      Digit[0][7] = false;

      Digit[1][0] = false;
      Digit[1][1] = true;
      Digit[1][2] = false;
      Digit[1][3] = false;
      Digit[1][4] = false;
      Digit[1][5] = true;
      Digit[1][6] = false;
      Digit[1][7] = false;

      Digit[2][0] = false;
      Digit[2][1] = false;
      Digit[2][2] = false;
      Digit[2][3] = false;
      Digit[2][4] = false;
      Digit[2][5] = true;
      Digit[2][6] = false;
      Digit[2][7] = false;

      Digit[3][0] = false;
      Digit[3][1] = false;
      Digit[3][2] = false;
      Digit[3][3] = true;
      Digit[3][4] = true;
      Digit[3][5] = false;
      Digit[3][6] = false;
      Digit[3][7] = false;

      Digit[4][0] = false;
      Digit[4][1] = false;
      Digit[4][2] = false;
      Digit[4][3] = false;
      Digit[4][4] = false;
      Digit[4][5] = true;
      Digit[4][6] = false;
      Digit[4][7] = false;

      Digit[5][0] = false;
      Digit[5][1] = false;
      Digit[5][2] = false;
      Digit[5][3] = false;
      Digit[5][4] = false;
      Digit[5][5] = true;
      Digit[5][6] = false;
      Digit[5][7] = false;

      Digit[6][0] = false;
      Digit[6][1] = true;
      Digit[6][2] = false;
      Digit[6][3] = false;
      Digit[6][4] = false;
      Digit[6][5] = true;
      Digit[6][6] = false;
      Digit[6][7] = false;

      Digit[7][0] = false;
      Digit[7][1] = false;
      Digit[7][2] = true;
      Digit[7][3] = true;
      Digit[7][4] = true;
      Digit[7][5] = false;
      Digit[7][6] = false;
      Digit[7][7] = false;
      break;

    case 4:
      Digit[0][0] = false;
      Digit[0][1] = false;
      Digit[0][2] = false;
      Digit[0][3] = false;
      Digit[0][4] = false;
      Digit[0][5] = false;
      Digit[0][6] = false;
      Digit[0][7] = false;

      Digit[1][0] = false;
      Digit[1][1] = false;
      Digit[1][2] = false;
      Digit[1][3] = false;
      Digit[1][4] = true;
      Digit[1][5] = true;
      Digit[1][6] = false;
      Digit[1][7] = false;

      Digit[2][0] = false;
      Digit[2][1] = false;
      Digit[2][2] = false;
      Digit[2][3] = true;
      Digit[2][4] = false;
      Digit[2][5] = true;
      Digit[2][6] = false;
      Digit[2][7] = false;

      Digit[3][0] = false;
      Digit[3][1] = false;
      Digit[3][2] = true;
      Digit[3][3] = false;
      Digit[3][4] = false;
      Digit[3][5] = true;
      Digit[3][6] = false;
      Digit[3][7] = false;

      Digit[4][0] = false;
      Digit[4][1] = true;
      Digit[4][2] = false;
      Digit[4][3] = false;
      Digit[4][4] = false;
      Digit[4][5] = true;
      Digit[4][6] = false;
      Digit[4][7] = false;

      Digit[5][0] = false;
      Digit[5][1] = true;
      Digit[5][2] = true;
      Digit[5][3] = true;
      Digit[5][4] = true;
      Digit[5][5] = true;
      Digit[5][6] = false;
      Digit[5][7] = false;

      Digit[6][0] = false;
      Digit[6][1] = false;
      Digit[6][2] = false;
      Digit[6][3] = false;
      Digit[6][4] = false;
      Digit[6][5] = true;
      Digit[6][6] = false;
      Digit[6][7] = false;

      Digit[7][0] = false;
      Digit[7][1] = false;
      Digit[7][2] = false;
      Digit[7][3] = false;
      Digit[7][4] = false;
      Digit[7][5] = true;
      Digit[7][6] = false;
      Digit[7][7] = false;
      break;

    case 5:
      Digit[0][0] = false;
      Digit[0][1] = true;
      Digit[0][2] = true;
      Digit[0][3] = true;
      Digit[0][4] = true;
      Digit[0][5] = false;
      Digit[0][6] = false;
      Digit[0][7] = false;

      Digit[1][0] = false;
      Digit[1][1] = true;
      Digit[1][2] = false;
      Digit[1][3] = false;
      Digit[1][4] = false;
      Digit[1][5] = false;
      Digit[1][6] = false;
      Digit[1][7] = false;

      Digit[2][0] = false;
      Digit[2][1] = true;
      Digit[2][2] = false;
      Digit[2][3] = false;
      Digit[2][4] = false;
      Digit[2][5] = false;
      Digit[2][6] = false;
      Digit[2][7] = false;

      Digit[3][0] = false;
      Digit[3][1] = true;
      Digit[3][2] = true;
      Digit[3][3] = true;
      Digit[3][4] = true;
      Digit[3][5] = false;
      Digit[3][6] = false;
      Digit[3][7] = false;

      Digit[4][0] = false;
      Digit[4][1] = false;
      Digit[4][2] = false;
      Digit[4][3] = false;
      Digit[4][4] = false;
      Digit[4][5] = true;
      Digit[4][6] = false;
      Digit[4][7] = false;

      Digit[5][0] = false;
      Digit[5][1] = false;
      Digit[5][2] = false;
      Digit[5][3] = false;
      Digit[5][4] = false;
      Digit[5][5] = true;
      Digit[5][6] = false;
      Digit[5][7] = false;

      Digit[6][0] = false;
      Digit[6][1] = true;
      Digit[6][2] = false;
      Digit[6][3] = false;
      Digit[6][4] = false;
      Digit[6][5] = true;
      Digit[6][6] = false;
      Digit[6][7] = false;

      Digit[7][0] = false;
      Digit[7][1] = false;
      Digit[7][2] = true;
      Digit[7][3] = true;
      Digit[7][4] = true;
      Digit[7][5] = false;
      Digit[7][6] = false;
      Digit[7][7] = false;
      break;

    case 6:
      Digit[0][0] = false;
      Digit[0][1] = false;
      Digit[0][2] = true;
      Digit[0][3] = true;
      Digit[0][4] = true;
      Digit[0][5] = false;
      Digit[0][6] = false;
      Digit[0][7] = false;

      Digit[1][0] = false;
      Digit[1][1] = true;
      Digit[1][2] = false;
      Digit[1][3] = false;
      Digit[1][4] = false;
      Digit[1][5] = true;
      Digit[1][6] = false;
      Digit[1][7] = false;

      Digit[2][0] = false;
      Digit[2][1] = true;
      Digit[2][2] = false;
      Digit[2][3] = false;
      Digit[2][4] = false;
      Digit[2][5] = false;
      Digit[2][6] = false;
      Digit[2][7] = false;

      Digit[3][0] = false;
      Digit[3][1] = true;
      Digit[3][2] = true;
      Digit[3][3] = true;
      Digit[3][4] = true;
      Digit[3][5] = false;
      Digit[3][6] = false;
      Digit[3][7] = false;

      Digit[4][0] = false;
      Digit[4][1] = true;
      Digit[4][2] = false;
      Digit[4][3] = false;
      Digit[4][4] = false;
      Digit[4][5] = true;
      Digit[4][6] = false;
      Digit[4][7] = false;

      Digit[5][0] = false;
      Digit[5][1] = true;
      Digit[5][2] = false;
      Digit[5][3] = false;
      Digit[5][4] = false;
      Digit[5][5] = true;
      Digit[5][6] = false;
      Digit[5][7] = false;

      Digit[6][0] = false;
      Digit[6][1] = true;
      Digit[6][2] = false;
      Digit[6][3] = false;
      Digit[6][4] = false;
      Digit[6][5] = true;
      Digit[6][6] = false;
      Digit[6][7] = false;

      Digit[7][0] = false;
      Digit[7][1] = false;
      Digit[7][2] = true;
      Digit[7][3] = true;
      Digit[7][4] = true;
      Digit[7][5] = false;
      Digit[7][6] = false;
      Digit[7][7] = false;
      break;

    case 7:
      Digit[0][0] = false;
      Digit[0][1] = true;
      Digit[0][2] = true;
      Digit[0][3] = true;
      Digit[0][4] = true;
      Digit[0][5] = true;
      Digit[0][6] = false;
      Digit[0][7] = false;

      Digit[1][0] = false;
      Digit[1][1] = false;
      Digit[1][2] = false;
      Digit[1][3] = false;
      Digit[1][4] = false;
      Digit[1][5] = true;
      Digit[1][6] = false;
      Digit[1][7] = false;

      Digit[2][0] = false;
      Digit[2][1] = false;
      Digit[2][2] = false;
      Digit[2][3] = false;
      Digit[2][4] = false;
      Digit[2][5] = true;
      Digit[2][6] = false;
      Digit[2][7] = false;

      Digit[3][0] = false;
      Digit[3][1] = false;
      Digit[3][2] = false;
      Digit[3][3] = false;
      Digit[3][4] = true;
      Digit[3][5] = false;
      Digit[3][6] = false;
      Digit[3][7] = false;

      Digit[4][0] = false;
      Digit[4][1] = false;
      Digit[4][2] = false;
      Digit[4][3] = true;
      Digit[4][4] = false;
      Digit[4][5] = false;
      Digit[4][6] = false;
      Digit[4][7] = false;

      Digit[5][0] = false;
      Digit[5][1] = false;
      Digit[5][2] = true;
      Digit[5][3] = false;
      Digit[5][4] = false;
      Digit[5][5] = false;
      Digit[5][6] = false;
      Digit[5][7] = false;

      Digit[6][0] = false;
      Digit[6][1] = false;
      Digit[6][2] = true;
      Digit[6][3] = false;
      Digit[6][4] = false;
      Digit[6][5] = false;
      Digit[6][6] = false;
      Digit[6][7] = false;

      Digit[7][0] = false;
      Digit[7][1] = false;
      Digit[7][2] = true;
      Digit[7][3] = false;
      Digit[7][4] = false;
      Digit[7][5] = false;
      Digit[7][6] = false;
      Digit[7][7] = false;
      break;

    case 8:
      Digit[0][0] = false;
      Digit[0][1] = false;
      Digit[0][2] = true;
      Digit[0][3] = true;
      Digit[0][4] = true;
      Digit[0][5] = false;
      Digit[0][6] = false;
      Digit[0][7] = false;

      Digit[1][0] = false;
      Digit[1][1] = true;
      Digit[1][2] = false;
      Digit[1][3] = false;
      Digit[1][4] = false;
      Digit[1][5] = true;
      Digit[1][6] = false;
      Digit[1][7] = false;

      Digit[2][0] = false;
      Digit[2][1] = true;
      Digit[2][2] = false;
      Digit[2][3] = false;
      Digit[2][4] = false;
      Digit[2][5] = true;
      Digit[2][6] = false;
      Digit[2][7] = false;

      Digit[3][0] = false;
      Digit[3][1] = false;
      Digit[3][2] = true;
      Digit[3][3] = true;
      Digit[3][4] = true;
      Digit[3][5] = false;
      Digit[3][6] = false;
      Digit[3][7] = false;

      Digit[4][0] = false;
      Digit[4][1] = true;
      Digit[4][2] = false;
      Digit[4][3] = false;
      Digit[4][4] = false;
      Digit[4][5] = true;
      Digit[4][6] = false;
      Digit[4][7] = false;

      Digit[5][0] = false;
      Digit[5][1] = true;
      Digit[5][2] = false;
      Digit[5][3] = false;
      Digit[5][4] = false;
      Digit[5][5] = true;
      Digit[5][6] = false;
      Digit[5][7] = false;

      Digit[6][0] = false;
      Digit[6][1] = true;
      Digit[6][2] = false;
      Digit[6][3] = false;
      Digit[6][4] = false;
      Digit[6][5] = true;
      Digit[6][6] = false;
      Digit[6][7] = false;

      Digit[7][0] = false;
      Digit[7][1] = false;
      Digit[7][2] = true;
      Digit[7][3] = true;
      Digit[7][4] = true;
      Digit[7][5] = false;
      Digit[7][6] = false;
      Digit[7][7] = false;
      break;

    case 9:
      Digit[0][0] = false;
      Digit[0][1] = false;
      Digit[0][2] = true;
      Digit[0][3] = true;
      Digit[0][4] = true;
      Digit[0][5] = false;
      Digit[0][6] = false;
      Digit[0][7] = false;

      Digit[1][0] = false;
      Digit[1][1] = true;
      Digit[1][2] = false;
      Digit[1][3] = false;
      Digit[1][4] = false;
      Digit[1][5] = true;
      Digit[1][6] = false;
      Digit[1][7] = false;

      Digit[2][0] = false;
      Digit[2][1] = true;
      Digit[2][2] = false;
      Digit[2][3] = false;
      Digit[2][4] = false;
      Digit[2][5] = true;
      Digit[2][6] = false;
      Digit[2][7] = false;

      Digit[3][0] = false;
      Digit[3][1] = true;
      Digit[3][2] = false;
      Digit[3][3] = false;
      Digit[3][4] = false;
      Digit[3][5] = true;
      Digit[3][6] = false;
      Digit[3][7] = false;

      Digit[4][0] = false;
      Digit[4][1] = false;
      Digit[4][2] = true;
      Digit[4][3] = true;
      Digit[4][4] = true;
      Digit[4][5] = true;
      Digit[4][6] = false;
      Digit[4][7] = false;

      Digit[5][0] = false;
      Digit[5][1] = false;
      Digit[5][2] = false;
      Digit[5][3] = false;
      Digit[5][4] = false;
      Digit[5][5] = true;
      Digit[5][6] = false;
      Digit[5][7] = false;

      Digit[6][0] = false;
      Digit[6][1] = true;
      Digit[6][2] = false;
      Digit[6][3] = false;
      Digit[6][4] = false;
      Digit[6][5] = true;
      Digit[6][6] = false;
      Digit[6][7] = false;

      Digit[7][0] = false;
      Digit[7][1] = false;
      Digit[7][2] = true;
      Digit[7][3] = true;
      Digit[7][4] = true;
      Digit[7][5] = false;
      Digit[7][6] = false;
      Digit[7][7] = false;
      break;

    case 0:
      Digit[0][0] = false;
      Digit[0][1] = false;
      Digit[0][2] = true;
      Digit[0][3] = true;
      Digit[0][4] = true;
      Digit[0][5] = false;
      Digit[0][6] = false;
      Digit[0][7] = false;

      Digit[1][0] = false;
      Digit[1][1] = true;
      Digit[1][2] = false;
      Digit[1][3] = false;
      Digit[1][4] = false;
      Digit[1][5] = true;
      Digit[1][6] = false;
      Digit[1][7] = false;

      Digit[2][0] = false;
      Digit[2][1] = true;
      Digit[2][2] = false;
      Digit[2][3] = false;
      Digit[2][4] = false;
      Digit[2][5] = true;
      Digit[2][6] = false;
      Digit[2][7] = false;

      Digit[3][0] = false;
      Digit[3][1] = true;
      Digit[3][2] = false;
      Digit[3][3] = false;
      Digit[3][4] = false;
      Digit[3][5] = true;
      Digit[3][6] = false;
      Digit[3][7] = false;

      Digit[4][0] = false;
      Digit[4][1] = true;
      Digit[4][2] = false;
      Digit[4][3] = false;
      Digit[4][4] = false;
      Digit[4][5] = true;
      Digit[4][6] = false;
      Digit[4][7] = false;

      Digit[5][0] = false;
      Digit[5][1] = true;
      Digit[5][2] = false;
      Digit[5][3] = false;
      Digit[5][4] = false;
      Digit[5][5] = true;
      Digit[5][6] = false;
      Digit[5][7] = false;

      Digit[6][0] = false;
      Digit[6][1] = true;
      Digit[6][2] = false;
      Digit[6][3] = false;
      Digit[6][4] = false;
      Digit[6][5] = true;
      Digit[6][6] = false;
      Digit[6][7] = false;

      Digit[7][0] = false;
      Digit[7][1] = false;
      Digit[7][2] = true;
      Digit[7][3] = true;
      Digit[7][4] = true;
      Digit[7][5] = false;
      Digit[7][6] = false;
      Digit[7][7] = false;
      break;
  }
}

void loop() {
  //if (code >= 0) { // execute puzzle when program has gotten its code
  unsigned long current_time = millis(); //get current time
  xValue = analogRead(X_PIN); //get initial xValue
  yValue = analogRead(Y_PIN); //get intial yValue
  if (yValue < 520) { //joystick is pointing up
    for (int row = 7; row >= 0; row--) { //iterate over 8 rows en 8 cols from right down to left up
      for (int col = 7; col >= 0; col--) {
        if (delaytime > 100) {
          max_reached = current_time;
          maximum = false;
        }
        else if (delaytime <= 100 && ! maximum) {
          max_reached = millis();
          maximum = true;
          Serial.println("hey" + current_time - max_reached);
        }
        lc.setLed(0, row, col,  Digit[row][col]); //setLed method: 0 = address (only for multiple displays), row, col, true/1 = led on and false/0 = led off
        delay(delaytime);
        if ( current_time <= max_reached + 3000) {
          lc.clearDisplay(0);
        }
        int yValue2 = analogRead(Y_PIN);
        if ( yValue2 < yValue - 10 || yValue2 > yValue + 10 ) { //check if yValue changed, margin for hysteresis
          break;
        }
      }
    }
  }

  //case joystick mid or pointing down (DEFAULT)
  else {
    for (int row = 0; row < 8; row++) { //iterate over 8 rows en 8 cols from left up to right down
      for (int col = 0; col < 8; col++) {
        if (delaytime > 100) {
          max_reached = current_time;
          maximum = false;
        }
        else if (delaytime < 100 && ! maximum) {
          max_reached = millis();
          maximum = true;
        }
        lc.setLed(0, row, col, Digit[row][col]); //setLed method: 0 = address (only for multiple displays), row, col, true/1 = led on and false/0 = led off
        delay(delaytime);
        lc.clearDisplay(0); //clears entire display
        delay(delaytime);
        xValue = analogRead(X_PIN);
        if (xValue > 700 && delaytime > 100 ) { //joystick pointing right, room for hysteresis
          delaytime -= 100;
        }
        else if (xValue < 300 && delaytime <= 1000) { //joystick pointing left, margin for hysteresis
          delaytime += 100;
        }
        int yValue2 = analogRead(Y_PIN);
        if ( yValue2 < yValue - 10 || yValue2 > yValue + 10 ) { //check if yValue changed, margin for hysteresis
          yValue = yValue2;
          break;
        }
      }
    }
  }
}
//}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int code = Wire.read();    // receive byte as an integer
  Serial.println(code);         // print the integer
}

void puzzleSolved() {
  Wire.write(solved);
}
