#include <Wire.h>

String inputStr=""; 
int dotT = 300, dashT=900, pauseT=1500; //Wachttijd van puntje, streepje en pauze tussen karakters
const int arduinoID = 10;         // MOET UNIQUE ZIJN T.O.V ANDERE ARDUINOS !!!
int code = -1;
int solved = 1;  // 1 == solved, 0 != solved
const int dotPin=2;
String cijfers[10] = {"NUL", "EEN", "TWEE", "DRIE", "VIER", "VIJF", "ZES", "ZEVEN", "ACHT", "NEGEN"};

void setup() {
  Wire.begin(arduinoID);         // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(puzzleSolved);
  Serial.begin(115200);  
  pinMode(dotPin, OUTPUT); 
  digitalWrite(dotPin,HIGH); // start serial for output
}

void loop() {
  if (code >= 0) { // do, als code ontvangen is (dus boven 0 ligt)
   int len= inputStr.length(); 
  
  for(int i=0; i<= (len-1); i++){ //neemt elke letter van de string en zet die om naar morse (de functie van die letter)
    char dispChar = inputStr.charAt(i); 
    convertToMorse(dispChar); 
  }
  
  while(10000); //wachttijd na alle karakters van de String
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
  Serial.println(code);  // print the integer
  inputStr = cijfers[code];
 
}

void puzzleSolved() {
    Wire.write(solved);
}

//Puntje
void dot(){
  digitalWrite(dotPin, LOW); //AAN
  delay(dotT); //Wachttijd
  digitalWrite(dotPin, HIGH); //UIT
  delay(dotT); 
}

//Streepje
void dash(){
  digitalWrite(dotPin, LOW); //AAN
  delay(dashT);  //Wachttijd
  digitalWrite(dotPin, HIGH); //UIT
  delay(dotT); 
}

//Pauzeer tss karaters
void pauseTime(){
  delay(pauseT); 
}
