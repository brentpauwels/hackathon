/*
  Project: 8x8 dot LED matrix common anode 1688 BS
  Function: Show text messages, symbols on an 8x8 led matrix, scrolling from right to left. Uses FrequencyTimer2 library to
           constantly run an interrupt routine at a specified frequency. This refreshes the display without the
           main loop having to do anything. YOU CAN CHANGE THE TEXT VERY EASY
*/
//**********************************************************************************************
#include <FrequencyTimer2.h>//include library code
//**********************************************************************************************
#define SPACE { \
    {0, 0, 0, 0, 0, 0, 0, 0},  \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0},\
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}\
  }
#define ALL { \
    {1, 1, 1, 1, 1, 1, 1, 1},  \
    {1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1},\
    {1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1}\
  }
#define Heart { \
    {0, 1, 1, 0, 0, 1, 1, 0},\
    {1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1}, \
    {0, 1, 1, 1, 1, 1, 1, 0}, \
    {0, 0, 1, 1, 1, 1, 0, 0}, \
    {0, 0, 0, 1, 1, 0, 0, 0} \
  }
#define One {\
    {0,0,0,1,0,0,0,0}, \
    {0,0,1,1,0,0,0,0},\
    {0,0,0,1,0,0,0,0},\
    {0,0,0,1,0,0,0,0},\
    {0,0,0,1,0,0,0,0},\
    {0,0,0,1,0,0,0,0},\
    {0,0,0,1,0,0,0,0},\
    {0,0,1,1,1,0,0,0}\
  }
#define Two{\
    {0,0,1,1,1,0,0,0},\
    {0,1,0,0,0,1,0,0},\
    {0,0,0,0,0,1,0,0},\
    {0,0,0,0,0,1,0,0},\
    {0,0,0,0,1,0,0,0},\
    {0,0,0,1,0,0,0,0},\
    {0,0,1,0,0,0,0,0},\
    {0,1,1,1,1,1,0,0}\
  }
#define Three {\
    {0,0,1,1,1,0,0,0},\
    {0,1,0,0,0,1,0,0},\
    {0,0,0,0,0,1,0,0},\
    {0,0,0,1,1,0,0,0},\
    {0,0,0,0,0,1,0,0},\
    {0,0,0,0,0,1,0,0},\
    {0,1,0,0,0,1,0,0},\
    {0,0,1,1,1,0,0,0}}

#define Four  {\
    {0,0,0,0,0,0,0,0},\
    {0,0,0,0,1,1,0,0},\
    {0,0,0,1,0,1,0,0},\
    {0,0,1,0,0,1,0,0},\
    {0,1,0,0,0,1,0,0},\
    {0,1,1,1,1,1,0,0},\
    {0,0,0,0,0,1,0,0},\
    {0,0,0,0,0,1,0,0}}

#define Five {\
    {0,1,1,1,1,1,0,0},\
    {0,1,0,0,0,0,0,0},\
    {0,1,0,0,0,0,0,0},\
    {0,1,1,1,1,0,0,0},\
    {0,0,0,0,0,1,0,0},\
    {0,0,0,0,0,1,0,0},\
    {0,1,0,0,0,1,0,0},\
    {0,0,1,1,1,0,0,0}}

#define Six {\
    {0,0,1,1,1,0,0,0},\
    {0,1,0,0,0,1,0,0},\
    {0,1,0,0,0,0,0,0},\
    {0,1,1,1,1,0,0,0},\
    {0,1,0,0,0,1,0,0},\
    {0,1,0,0,0,1,0,0},\
    {0,1,0,0,0,1,0,0},\
    {0,0,1,1,1,0,0,0}}

#define Seven {\
  {0,1,1,1,1,1,0,0},\
  {0,0,0,0,0,1,0,0},\
  {0,0,0,0,0,1,0,0},\
  {0,0,0,0,1,0,0,0},\
  {0,0,0,1,0,0,0,0},\
  {0,0,1,0,0,0,0,0},\
  {0,0,1,0,0,0,0,0},\
  {0,0,1,0,0,0,0,0}}
#define Eight {\
  {0,0,1,1,1,0,0,0},\
  {0,1,0,0,0,1,0,0},\
  {0,1,0,0,0,1,0,0},\
  {0,0,1,1,1,0,0,0},\
  {0,1,0,0,0,1,0,0},\
  {0,1,0,0,0,1,0,0},\
  {0,1,0,0,0,1,0,0},\
  {0,0,1,1,1,0,0,0}}
  #define Nine {\
  {0,0,1,1,1,0,0,0},\
  {0,1,0,0,0,1,0,0},\
  {0,1,0,0,0,1,0,0},\
  {0,1,0,0,0,1,0,0},\
  {0,0,1,1,1,1,0,0},\
  {0,0,0,0,0,1,0,0},\
  {0,1,0,0,0,1,0,0},\
  {0,0,1,1,1,0,0,0}}
  #define Zero {\
  {0,0,1,1,1,0,0,0},\
  {0,1,0,0,0,1,0,0},\
  {0,1,0,0,0,1,0,0},\
  {0,1,0,0,0,1,0,0},\
  {0,1,0,0,0,1,0,0},\
  {0,1,0,0,0,1,0,0},\
  {0,1,0,0,0,1,0,0},\
  {0,0,1,1,1,0,0,0}}
int pattern = 0;
byte col = 0;
byte leds[8][8];
//(-1 is dummy to make array start at pos 1)
int pins[17] = { -1, 13, 12, 11, 10, 16, 17, 18, 19 , 2, 3, 4, 5, 6, 7, 8, 9}; //- Arduino Uno board pins
//see here for reference 8x8 dot LED matrix pins - int pins[17]= {-1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
int cols[8] = {pins[13], pins[3], pins[4], pins[10], pins[6], pins[11], pins[15], pins[16]};//columns of leds = pin on led matrix
int rows[8] = {pins[9], pins[14], pins[8], pins[12], pins[1], pins[7], pins[2], pins[5]};//rows of leds = pin on led matrix
//*******************************************************************************************************************************************************
//PLACE WERE YOU CAN CHANGE THE TEXT
const int numPatterns = 10;//CHANGE THIS NUMBER 21 depending on your symbols quantity below
//W, E, L, C, O, M, E, SPACE, T, O, SPACE, A, C, O, P, T, E, X,SPACE,Heart,SPACE - you can change this to your message, in this example
//21 symbols used separated by commas
byte patterns[numPatterns][8][8] = {One, Two, Three, Four, Five, Six, Seven, Eight, Nine, Zero};
//********************************************************************************************************************************************************
void setup() {
  for (int i = 1; i <= 16; i++) {
    pinMode(pins[i], OUTPUT);//sets 8x8 dot LED matrix pins as OUTPUT
  }
  for (int i = 1; i <= 8; i++) {//setup 8x8 dot LED matrix columns and rows
    digitalWrite(cols[i - 1], HIGH);
    digitalWrite(rows[i - 1], HIGH);
  }
  //for (int i = 1; i <= 8; i++) {  //}
  clearLeds();
  FrequencyTimer2::disable();//turns off toggling of pin 11
  FrequencyTimer2::setPeriod(2000);//sets refresh rate (interrupt timeout period)
  FrequencyTimer2::setOnOverflow(display);//sets interrupt routine to be called
  setPattern(pattern);
}
void loop() {
  pattern = ++pattern % numPatterns;
  slidePattern(pattern, 100); //patroon hebben we gebouwd hierboven, 2e var is om delay te bepalen voor het patroon opschuift
}
//*********************************************************************************************
void clearLeds() {//clears display array
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      leds[i][j] = 0;
    }
  }
}
//*********************************************************************************************
void setPattern(int pattern) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      leds[i][j] = patterns[pattern][i][j];
    }
  }
}
//********************************************************************************************
void slidePattern(int pattern, int del) {
  for (int l = 0; l < 8; l++) {
    for (int i = 0; i < 7; i++) {
      for (int j = 0; j < 8; j++) {
        leds[j][i] = leds[j][i + 1];
      }
    }
    for (int j = 0; j < 8; j++) {
      leds[j][7] = patterns[pattern][j][0 + l];
    }
    delay(del);
  }
}
//*********************************************************************************************
void display() {                  //interrupts routine
  digitalWrite(cols[col], HIGH);  //turns whole previous column off
  col++;
  if (col == 8) {
    col = 0;
  }
  for (int row = 0; row < 8; row++) {
    if (leds[col][7 - row] == 1) {
      digitalWrite(rows[row], HIGH);  //turns on this led
    }
    else {
      digitalWrite(rows[row], LOW);   //turns off this led
    }
  }
  digitalWrite(cols[col], LOW);       //turns whole column on at once (for equal lighting times)
}
