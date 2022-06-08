#include <Wire.h>

const int arduinoID = 12;         // MOET UNIQUE ZIJN T.O.V ANDERE ARDUINOS !!!
int code = -1;
int solved = 1;                  // 1 == solved, 0 != solved


int analogPin = A0;
bool opgelost = false;
bool goedeTemp = false;
unsigned long startOven = 0;

void setup() {
  // put your setup code here, to run once:Wire.begin(arduinoID);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(puzzleSolved);
  pinMode(analogPin, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
  digitalWrite(13, LOW);
  digitalWrite(8, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (code >= 0) {
      int val = analogRead(analogPin);
      //delay(250); 
        Serial.println(val);
        Serial.println(startOven);
        if(val <= 1024 && val >= 650){
          goedeTemp = true;
          Serial.println("goede temp");
        }else{
          startOven = 0;
          goedeTemp = false;
          Serial.println("slechte temp");
          digitalWrite(13, LOW);
          Serial.println(val);
        }
        if(startOven == 0 && goedeTemp){
            startOven = millis();
            Serial.println("start oven");
            digitalWrite(13, HIGH);
        }
    if(startOven !=0 && millis() >= startOven+6000){
            opgelost = true;
            Serial.println("vuur is langgenoeg warm");
            digitalWrite(8, HIGH);
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
