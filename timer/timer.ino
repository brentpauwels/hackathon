/*   hulp bij verbinden 7segment en timer
 *   https://haneefputtur.com/7-segment-4-digit-led-display-sma420564-using-arduino.html
 */

#include "SevSeg.h"

SevSeg sevseg; //Instantiate a seven segment controller object

 void setup() {
 byte numDigits = 4; 
 byte digitPins[] = {13, 12, 11, 10};
 byte segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
 bool leadingZeros = true;

 Serial.begin(9600);

sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins); 
// If your display is common anode type, please edit comment above line and uncomment below line
// sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);
sevseg.setBrightness(90);
}

void loop() {
 static unsigned long timer = millis();
 static int deciSeconds = 0;
 
 if (millis() >= timer) {
 deciSeconds++; // 1000 milliSeconds is equal to 10 deciSecond
 timer += 1000; 
 if (deciSeconds == 18000) { // Reset to 0 after counting for 1000 seconds.
 sevseg.setNumber(0,2);
 }
 //Serial.println(berekenTijd(deciSeconds));
 sevseg.setNumber(berekenTijd(deciSeconds), 2);
 }

 sevseg.refreshDisplay(); // Must run repeatedly
}

int berekenTijd(int deci){
  int tijdInSec = 1800 - deci;
  int min = tijdInSec/60;
  int tijd = (min*100)+(tijdInSec-(min*60));
  Serial.println(tijd);
  return tijd;
}
