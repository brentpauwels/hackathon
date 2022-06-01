#include "LedControl.h"
//source LedControl: http://wayoda.github.io/LedControl/
//source joystick: https://arduinogetstarted.com/tutorials/arduino-joystick

int Heart[8][8] {
  {0, 1, 1, 0, 0, 1, 1, 0},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {0, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0}
};
int One[8][8] = {
  {0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 0, 0, 0}
};
int Two[8][8] = {
  {0, 0, 1, 1, 1, 0, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 1, 1, 0, 0}
};
int Three[8][8] = {
  {0, 0, 1, 1, 1, 0, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 0, 1, 1, 1, 0, 0, 0}
};

int Four[8][8] =  {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 1, 0, 0},
  {0, 0, 0, 1, 0, 1, 0, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 1, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0}
};

int Five[8][8] = {
  {0, 1, 1, 1, 1, 1, 0, 0},
  {0, 1, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 0, 1, 1, 1, 0, 0, 0}
};

int Six[8][8] = {
  {0, 0, 1, 1, 1, 0, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 1, 0, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 0, 1, 1, 1, 0, 0, 0}
};

int Seven[8][8] = {
  {0, 1, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0}
};
int Eight[8][8] = {
  {0, 0, 1, 1, 1, 0, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 0, 1, 1, 1, 0, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 0, 1, 1, 1, 0, 0, 0}
};
int Nine[8][8] = {
  {0, 0, 1, 1, 1, 0, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 0, 1, 1, 1, 0, 0, 0}
};
int Zero[8][8] = {
  {0, 0, 1, 1, 1, 0, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 0, 1, 1, 1, 0, 0, 0}
};

LedControl lc = LedControl(12, 11, 10, 1); //12 = DataIn, 11 = CLK, 10 = LOAD

#define X_PIN  A0 // joystick X_PIN analoge pin
#define Y_PIN  A1 // joystick Y_PIN analoge pin 
int xValue = 0; // xCo opslag, default voor x is  513, volledig links = 0, rechts = 1023
int yValue = 0; // yCo opslag default voor y is 521, volledig boven = 0, beneden = 1023
unsigned long delaytime = 1000; //startdelay

void setup() {
  Serial.begin(9600); //joystick leest x en y als analoge waarden
  lc.shutdown(0, false); //maak IC wakker (default = powersaving sleep mode)
  lc.setIntensity(0, 10); //zet helderheid display tussen 0 en 15
  lc.clearDisplay(0); // zet hele display af
}

void matrix() {
  xValue = analogRead(X_PIN); //krijg initiele waarde van de joystick voor x
  yValue = analogRead(Y_PIN); //en voor y
  if (yValue > 521) { //joystick is naar beneden gericht
    for (int row = 7; row >= 0; row--) { //itereer over 8 rijen en 8 kolommen van rechtsonder naar linksboven
      for (int col = 7; col >= 0; col--) {
        int yValue2 = analogRead(Y_PIN);
        if ( yValue2 < yValue - 10 || yValue2 > yValue + 10 ) { //check of yValue veranderd is met ruimte voor hysteresis
          yValue = yValue2;
          break;
        }
        xValue = analogRead(X_PIN);
        if (xValue > 700 && delaytime > 10 ) { //joystick naar rechts met ruimte voor hysteresis
          delaytime -= 100;
        }
        else if (xValue < 300 && delaytime <= 1000) { //joystick naar links met ruimte voor hysteresis
          delaytime += 100;
        }
        if (Four[row][col] == 1) { //print getal
          lc.setLed(0, row, col, true); //setLed methode: 0 = id (enkel van toep bij meerdere displays), row = rij, col = kolom, true/1 = led aan en false/0 = led uit
          delay(delaytime);
          lc.clearDisplay(0);
        }
      }
    }
  }

  //geval joystick midden of omhoog (DEFAULT)
  else {
    for (int row = 0; row < 8; row++) { //itereer over 8 rijen en 8 kolommen linksboven naar rechtsonder
      for (int col = 0; col < 8; col++) {
        delay(delaytime);
        int yValue2 = analogRead(Y_PIN);
        if (yValue2 < yValue - 10 || yValue2 > yValue + 10 ) { //als yValue verandert doorheen de iteratie moet er bekeken worden of er andersom geprint moet worden
          yValue = yValue2;
          break;
        }
        xValue = analogRead(X_PIN);
        if (xValue > 700 && delaytime > 10 ) { //joystick naar rechts met ruimte voor hysteresis
          delaytime -= 100;
        }
        else if (xValue < 300 && delaytime <= 200) { //joystick naar links met ruimte voor hysteresis
          delaytime += 100;
        }
        if (Four[row][col] == 1) { //print getal
          lc.setLed(0, row, col, true); //setLed methode: 0 = id (enkel van toep bij meerdere displays), row = rij, col = kolom, true/1 = led aan en false/0 = led uit
          delay(delaytime);
          lc.clearDisplay(0);
        }
      }
    }
  }
}
void loop() {
  matrix();
}
