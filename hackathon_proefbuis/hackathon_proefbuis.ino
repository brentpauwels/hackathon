//source 7segment code: https://create.arduino.cc/projecthub/aboda243/get-started-with-seven-segment-c73200
#include <Wire.h>
const int arduinoID = 10;         // MOET UNIQUE ZIJN T.O.V ANDERE ARDUINOS !!!
int code = -1;
int solved = 1;                  // 1 == solved, 0 != solved
char c = -1;

byte Digits[10][8] {
  {'0', 1, 1, 1, 1, 1, 1, 0}, //0
  {'1', 0, 1, 1, 0, 0, 0, 0}, //1
  {'2', 1, 1, 0, 1, 1, 0, 1}, //2
  {'3', 1, 1, 1, 1, 0, 0, 1}, //3
  {'4', 0, 1, 1, 0, 0, 1, 1}, //4
  {'5', 1, 0, 1, 1, 0, 1, 1}, //5
  {'6', 1, 0, 1, 1, 1, 1, 1}, //6
  {'7', 1, 1, 1, 0, 0, 0, 0}, //7
  {'8', 1, 1, 1, 1, 1, 1, 1}, //8
  {'9', 1, 1, 1, 1, 0, 1, 1}, //9
};

#define A 12
#define B 11
#define C 10
#define D 9
#define E 8
#define F 7
#define G 6
int seg[] {A, B, C, D, E, F, G};        //note: no use for Decimal Point, so it's omitted
const int knop = 13;
int buttonState = 0;                    //button starts unpressed
void setup() {
  Wire.begin(arduinoID);                // join i2c bus with address #10
  Wire.onReceive(receiveEvent);         // register event
  Wire.onRequest(puzzleSolved);
  Serial.begin(115200);                 // start serial for output

  pinMode(seg[0], OUTPUT);              //all pins of the 7 segment are outputs
  pinMode(seg[1], OUTPUT);
  pinMode(seg[2], OUTPUT);
  pinMode(seg[3], OUTPUT);
  pinMode(seg[4], OUTPUT);
  pinMode(seg[5], OUTPUT);
  pinMode(seg[6], OUTPUT);
  pinMode(knop, INPUT);                 //button as input
}

void loop() {

  if (code >= 0) { // do, als code ontvangen is (dus boven 0 ligt)
    digitalRead(buttonState);
    if (digitalRead(buttonState) == HIGH) {                                 //button is pressed
      unsigned long button_pressed = millis();                             //unsigned because always >= 0
      if (millis() == button_pressed + 1000 && digitalRead(knop) == HIGH) { //make sure the button is pressed for at least 1 whole second before showing answer
        Print(c);
        solved = 1;
      }
    }
  }
  delay(1000);
  if (solved == 1) {
    solved = 0;
  }
}

void Print(char Char) {  // function for printing char
  int index = -1;     // set search result to -1
  for (int i = 0; i < 10 ; i++) { //search for the entered character
    if (Char == Digits[i][0]) { //if the character found
      index = i;//set the result number into index
    }
  }
  for (int i = 0; i < 8; i++) {
    digitalWrite(seg[i], Digits[index][i + 1]);
  }
}

void receiveEvent(int howMany) {
  while (1 < Wire.available()) {  // loop through all but the last
    char c = Wire.read();         // receive byte as a character
    Serial.print(c);              // print the character
  }

  code = Wire.read();            // receive byte as an integer
  Serial.println(code);         // print the integer

}

void puzzleSolved() {
  Wire.write(solved);
}
