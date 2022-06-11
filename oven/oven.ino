#include <Wire.h>
#include <Servo.h>

const int arduinoID = 12;         // MOET UNIQUE ZIJN T.O.V ANDERE ARDUINOS !!!
int code = -1;
int solved = 1;                  // 1 == solved, 0 != solved

Servo servo_9;
int analogPin = A0;
double graden;
bool opgelost = false;
bool goedeTemp = false;
unsigned long startOven = 0;

void setup() {
  // put your setup code here, to run once:Wire.begin(arduinoID);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(puzzleSolved);
  pinMode(analogPin, OUTPUT);
  servo_9.attach(9, 500, 2500);
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
      graden = val/5.7;
    servo_9.write(ceil(graden));
    Serial.println(val);
    Serial.println(ceil(graden));
      //delay(250);
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
            solved = 1;
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
