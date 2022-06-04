#include <Wire.h>

const int arduinoID = 8;         // MOET UNIQUE ZIJN T.O.V ANDERE ARDUINOS !!!
int code = -1;
int solved = 1;                  // 1 == solved, 0 != solved

void setup() {
  Wire.begin(arduinoID);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(puzzleSolved);
  Serial.begin(115200);           // start serial for output
}

void loop() {
  if (code >= 0) { // do, als code ontvangen is (dus boven 0 ligt)
   //do puzzle
    delay(1000);
    if (solved == 1) {
        solved = 0;
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
 
}

void puzzleSolved() {
    Wire.write(solved);
}
