#include <Arduino.h>
#define IR_INPUT_PIN 2
#include "TinyIRReceiver.hpp"
#include <Wire.h>

int inputRemote = 0;
volatile struct TinyIRReceiverCallbackDataStruct sCallbackData;

unsigned long timer = millis();
int waitTillNextRead = 500;
int arr[5] = {1, 2, 3, 4, 5};

int RPin = 9;
int GPin = 10;
int BPin = 11;
int ledcomp = 0;
int ledcount = 1;
boolean done = false;
boolean doneShowing = true;
int color;
unsigned int rgbColour[3];
const int buzzer = 3; //buzzer to arduino pin 9

const int arduinoID = 8;         // MOET UNIQUE ZIJN T.O.V ANDERE ARDUINOS !!!
int code = -1;
int solved = 1;                  // 1 != solved, 0 == solved

void setup()
{
  Serial.begin(115200);
  Wire.begin(arduinoID);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent);         // register event
  Wire.onRequest(puzzleSolved);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  initPCIInterruptForTinyReceiver();
}

void loop() {
  if (code >= 0) {
    if (solved == 1) {
      checkGameOn();
      if (done && !doneShowing && millis() - timer > 2000) {
      setColourRgb();
     }
     checkInput();
     if (millis() - timer > 500) {
      showColor(5);
    }
    } else {
      completed();
      delay(2000);
    }
  }
}
