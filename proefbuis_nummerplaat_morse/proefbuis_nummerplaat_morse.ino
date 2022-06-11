#include <Wire.h>
#include <SevenSegmentDisplay.h>
//source 7segment code: https://github.com/alikabeel/Letters-and-Numbers-Seven-Segment-Display-Library
/*
  Showing numbers, chars and phrases
                                A (segment 7, arduino pin 12)
                               ---
  F (segment 9, arduino pin 7)|   | B (segment 6, arduino pin 11)
                              |   |
                               --- G (segment 10, arduino pin 6)
  E (segment 1, arduino pin 8)|   |
                              |   | C (segment 4, arduino pin10)
                                ---  . (segment 5, arduino pin 5 )
                                 D (segment 2, arduino pin9)
*/
const int arduinoID = 10;         // MOET UNIQUE ZIJN T.O.V ANDERE ARDUINOS !!!
int code = -1;
int solved = 0;
char c = '0';
SevenSegmentDisplay digit(12, 11, 10, 9, 8, 7, 6, 5, false);  //initialization 7seg display according to library prescriptions
const int dotPin = 2;
const int button = 3;
const int hallPin = 4;
const unsigned long interval_time = 10000;
unsigned long starting_time;;
int buttonState = 0;                    //0 == LOW, 1 == HIGH
int sensorState = 0;                    //sensor starts 0
char help [5] = {'h', 'e', 'l', 'p', '_'};
char thanks [7] = {'t', 'h', 'a', 'n', 'k', 's', '_'};
char almost [7] = {'a', 'l', 'n', 'o', 's', 't', '_'};
String inputStr = "";
int dotT = 300, dashT = 900, pauseT = 1500; //Wachttijd van puntje, streepje en pauze tussen karakters
String cijfers[10] = {"NUL", "EEN", "TWEE", "DRIE", "VIER", "VIJF", "ZES", "ZEVEN", "ACHT", "NEGEN"};

void setup() {
  Wire.begin(arduinoID);                // join i2c bus with address #10
  Wire.onReceive(receiveEvent);         // register event
  Wire.onRequest(puzzleSolved);
  Serial.begin(115200);                 // start serial for output
  pinMode(button, INPUT); //button as input
  pinMode(hallPin, INPUT); // sensor leg as input
  starting_time = millis();
  pinMode(dotPin, OUTPUT);
  digitalWrite(dotPin, HIGH); // start serial for output

}

void loop() {
  if (code >= 0) { // only execute when master Arduino gave code
    sensorState = digitalRead(button);
    int len = inputStr.length();
    unsigned long current_time = millis();
    if ( current_time - starting_time >= interval_time) {
      for (int i = 0; i <= (len - 1); i++) { //converts every char to Morse equivalent
        char dispChar = inputStr.charAt(i);
        convertToMorse(dispChar);
      }
      starting_time = current_time;
    }
    if (buttonState && sensorState ) { //both games finished
      Serial.println(buttonState + " " + sensorState ); //debug
      delay(2000);
      if (buttonState && sensorState) { //make sure both games are finished for at least 2 whole seconds before showing answer
        for (int i = 0; i < 7; i++) {
          digit.displayCharacter(thanks[i]);
          delay(300);
        }
        solved = 1;
      }
    }
    else if (buttonState && ! sensorState || ! buttonState && sensorState) { //1 game finished
      for (int i = 0; i < 7; i++) { //show "almost"
        buttonState = digitalRead(button);
        sensorState = digitalRead(hallPin);
        if (buttonState == HIGH && sensorState == HIGH) { //break out of loop when possible solution is detected
          break;
        }
        digit.displayCharacter(almost[i]);
        delay(300);
      }
      delay(500);
    }
    else { //both games aren't finished yet
      for (int i = 0; i < 5; i++) { //show "help"
        buttonState = digitalRead(button);
        sensorState = digitalRead(hallPin);
        if (buttonState == HIGH && sensorState == HIGH) { //break out of loop when possible solution is detected
          break;
        }
        digit.displayCharacter(help[i]);
        delay(300);
      }
      delay(500);
    }
  }
}

//dot
void dot() {
  digitalWrite(dotPin, LOW); //ON
  delay(dotT); //wait
  digitalWrite(dotPin, HIGH); //OFF
  delay(dotT);
}

//dash
void dash() {
  digitalWrite(dotPin, LOW); //ON
  delay(dashT);  //wait
  digitalWrite(dotPin, HIGH); //OFF
  delay(dotT);
}

//pause between 2 chars
void pauseTime() {
  delay(pauseT);
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
