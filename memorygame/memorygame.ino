#include <Arduino.h>
#define IR_INPUT_PIN 2
#include "TinyIRReceiver.hpp"
int inputRemote = 0;
volatile struct TinyIRReceiverCallbackDataStruct sCallbackData;

unsigned long timer = millis();
int waitTillNextRead = 500;
int arr[] = {1, 2, 3, 4, 5};

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

void setup()
{
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  initPCIInterruptForTinyReceiver();
  randomSeed(analogRead(A0));
}

void loop() {

  if (inputRemote == 3 && done == false) {
    for (int i = 0; i < 5; i++) {
      arr[i] = (int)random(1, 5);
    }
    Serial.println(inputRemote);
    done = true;
    inputRemote = 0;
    doneShowing = false;
    timer = millis() + 2000;
    for (int i = 0; i < 5; i++) {
      Serial.print(arr[i]);
    }
  }


  if (done && !doneShowing && millis() - timer > 2000) {
    setColourRgb();
  }


  if (inputRemote > 0) {
    delay(200);
    if (inputRemote - 3 == arr[ledcomp] && doneShowing) {
      showColor(inputRemote - 3);
      tone(buzzer, 1500);
      Serial.println("true");
      delay(100);
      noTone(buzzer);
      ledcomp++;
      timer = millis();
      if (ledcomp == ledcount) {
        ledcount++;
        ledcomp = 0;
        doneShowing = false;
      }
      if (ledcount == 5){
        completed();
      }
    } else {
      for (int i = 0; i <= 3; i++) {
        showColor(1);
        tone(buzzer, 3);
        delay(250);
        noTone(buzzer);
        showColor(5);
        delay(200);
      }
      for (int i = 0; i < 5; i++) {
        color = (int)random(1, 5);
        arr[i] = color;
      }
      Serial.println(arr[0]);
      ledcomp = 0;
      ledcount = 1;
      doneShowing = false;
      delay(2000);
    }
    inputRemote = 0;
  }
  
  if (millis() - timer > 500) {
    showColor(5);
  }
}
