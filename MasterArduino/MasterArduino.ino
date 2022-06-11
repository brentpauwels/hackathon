#include <FastLED.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

#define POTENTIOMETER_PIN A0
#define LED_PIN     13
#define NUM_LEDS    30

char keys[4][3] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[4] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[3] = {6, 7, 8}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, 4, 3);

int reading;
int convertReading;

int code = 348;
int inputCode[5];

String elementsString[] = {"Ca", "Na", "S", "H", "Cl", "Ni", "He", "B", "Hg", "Mg" };
int moeilijkheid;
long sDigit;
long lDigit;
short codeArr[] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int elements[5];

boolean puzzleOneCompleted = false;
boolean puzzleTwoCompleted = false;
boolean puzzleThreeCompleted = false;
boolean puzzleFourCompleted = false;
boolean puzzleFiveCompleted = false;
boolean elementsDone = true;

unsigned long timer;
unsigned long receiveDelay = millis();
boolean standingStill = false;
int i = 0;
int y = 0;
int cursorPos = 0;

boolean gameDone = false;

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  Wire.begin();

  //code generator
  moeilijkheid = (int)firstDigit(code);
  sDigit = codeGen(firstDigit(code - (moeilijkheid * 100)) + 1);
  lDigit = codeGen(lastDigit(code) + 1);
  codeCheck();

  // puzzle elements on startup
  convertIntToElementNumber(moeilijkheid, codeArr);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

  // LCD on startup
  displayStart();
}

void loop() {
  if (!gameDone) {
    if (!elementsDone) {
    elementsPuzzle();
  }
  if (millis() - receiveDelay > 500) {
     puzzleOneCompleted = checkIfDone(8, 1, puzzleOneCompleted);
     puzzleTwoCompleted = checkIfDone(9, 2, puzzleTwoCompleted); 
     receiveDelay = millis();
  }
  char key = keypad.getKey();
  
  if (key){
    keyPressed(key);
  }
  delay(20);
  }
  
}
