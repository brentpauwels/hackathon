void displayStart() {
  lcd.init();
  lcd.backlight();
  String Elements = "";
  String digits = "";

  for (int i = 0; i < moeilijkheid + 2; i++) {
    Elements += "Xx ";
    digits += "X  ";
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(Elements);
  lcd.setCursor(0, 1);
  lcd.print(digits);
}


void showLeds(int o) {
  for (int x = 0; x <= i-1; x++) {
    leds[elements[x]] = CRGB(255, 255, 255);
  }
  leds[convertReading] = CRGB(y, 255, o);
  FastLED.show();
}


void showNewElement(int index) {
  lcd.setCursor(index * 3, 0);
  lcd.print(elementsString[codeArr[index + moeilijkheid + 2]]);
}


void convertIntToElementNumber(int moeilijkheid, int codeArr[]) {
  for (int a = 0; a < moeilijkheid + 2; a++) {
    elements[a] = cnvrtElementOnStrip(codeArr[a + moeilijkheid + 2]);
  }
}


int cnvrtElementOnStrip(int nr) {
  switch (nr) {
    case 0: return 17;
    case 1: return 5;
    case 2: return 24;
    case 3: return 28;
    case 4: return 15;
    case 5: return 13;
    case 6: return 7;
    case 7: return 21;
    case 8: return 1;
    case 9: return 10;

  }
}


long firstDigit(long n) {
  while (n >= 10)
    n /= 10;
  return n;
}


long lastDigit(long n) {
  return n % 10;
}


int codeGen(int n) {
  n = n * 127;
  return n;
}


void codeCheck() {
  if (moeilijkheid == 2) {
    sDigit *= 14;
    lDigit *= 13;
  } else if (moeilijkheid == 3) {
    sDigit *= 137;
    lDigit *= 133;
  }
  while (sDigit > pow(10, moeilijkheid + 2)) {
    sDigit /= 10;
  }
  while (lDigit > pow(10, moeilijkheid + 2)) {
    lDigit /= 10;
  }
  boolean doubble = false;
  while (!doubble) {
    doubble = true;
    for (int y = moeilijkheid + 1; y >= 1; y--) {
      int fDigit = lastDigit(lDigit / pow(10, y));
      for (int i = y - 1; i >= 0; i--) {
        if (fDigit == lastDigit(lDigit / pow(10, i))) {
          doubble = false;
          lDigit += pow(10, i);
          break;
        }
      }
    }
  }
  while (lDigit > pow(10, moeilijkheid + 2)) {
    lDigit /= 10;
  }
  Serial.print("Code: ");
  Serial.println(sDigit);
  Serial.print("Samenstelling: ");
  Serial.print(lDigit);
  int count = 0;
  for (int y = moeilijkheid + 2; y > 0; y--) {
    codeArr[count] = (lastDigit(sDigit / pow(10, y - 1)));
    codeArr[count + moeilijkheid + 2] = (lastDigit(lDigit / pow(10, y - 1)));
    count++;
  }
  Serial.println("oke");
  for (int y = 0; y <= moeilijkheid + 1; y++) {
    int a = codeArr[y];
    Wire.beginTransmission(y + 8); // transmit to device #8 and above
    Wire.write("Code number: ");        // sends five bytes
    Wire.write(a);              // sends one byte
    Wire.endTransmission();    // stop transmitting
  }
}

void elementsPuzzle() {
  FastLED.clear();
  reading = analogRead(POTENTIOMETER_PIN);
  convertReading = map(reading, 0, 667, 0, 29);
  if (convertReading == elements[i]) {
  y += 1;
  if (!standingStill) {
      Serial.print("Great");
      standingStill = true;
    }
  } else {
    standingStill = false;
  }

  if (standingStill && y > 255) {
  leds[convertReading] = CRGB(255, 255, 255);
    showNewElement(i);
    standingStill = false;
    y = 0;
    i++;
  } else if (standingStill) {
  showLeds(255);
  } else {
    showLeds(0);
  }
  if (i == moeilijkheid + 2) {
    FastLED.clear();
    FastLED.show();
    Serial.print("niceeee");
    elementsDone = true;
  }
  delay(20);
}


// check if its correct
boolean checkCorrectCode() {
  for (int y = 0; y <= moeilijkheid + 1; y++) {
    if (inputCode[y] != codeArr[y] || !elementsDone) {
      Serial.print("faulty code");
      return false;
    }
  }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Formula found!");
    String StringCode = "";
    for (int i = 0; i < moeilijkheid + 2; i++) {
    StringCode += codeArr[i];
    StringCode += elementsString[codeArr[i+moeilijkheid + 2]];
  }
  lcd.setCursor(0, 1);
  lcd.print(StringCode);
  return true;
}

// methode wich checks if puzzle from other arduino's are done
boolean checkIfDone(int id, int nthPuzzle, boolean puzzleDone) {
  if (!puzzleDone) {
    Wire.requestFrom(id, 1);     // request 1 bytes from slave device #8
    while (Wire.available()) { // slave may send less than requested
      int c = Wire.read();     // receive a byte as character
//      Serial.print("ARDUINO ");
//      Serial.print(nthPuzzle);
//      Serial.print(" :");
//      Serial.println(c);         // print the character
      if (c == 1) {
        return false;
      } else if (c == 0) {
        return true;
      }
      // Wire.end();
    }
  } else {
    return true;
  }
}


// check keypress
void keyPressed(char key) {
      if (key == '#') {
       gameDone = checkCorrectCode();
    } else if (key == '*' && cursorPos > 0) {
      cursorPos--;
    } else if ((int)key -48 >= 0) {
      inputCode[cursorPos] = (int)key - 48;
      lcd.setCursor(cursorPos*3, 1);
      lcd.print(inputCode[cursorPos]);
      if (cursorPos != moeilijkheid+1)
       cursorPos++;
    }
}
