
void showColor(int index) {
  setColor(index);
  analogWrite(RPin, rgbColour[0]);
  analogWrite(GPin, rgbColour[1]);
  analogWrite(BPin, rgbColour[2]);

}

void setColourRgb() {
  for (int i = 0; i < ledcount; i++) {
    setColor(arr[i]);
    Serial.println("done");
    analogWrite(RPin, rgbColour[0]);
    analogWrite(GPin, rgbColour[1]);
    analogWrite(BPin, rgbColour[2]);
    delay(500);
    analogWrite(RPin, 0);
    analogWrite(GPin, 0);
    analogWrite(BPin, 0);
    delay(250);
  }
  doneShowing = true;
}

void setColor(int index) {
  switch (index) {
    case 1:
      rgbColour[0] = 255;
      rgbColour[1] = 0;
      rgbColour[2] = 0;
      break;
    case 2:
      rgbColour[0] = 0;
      rgbColour[1] = 255;
      rgbColour[2] = 0;
      break;
    case 3:
      rgbColour[0] = 0;
      rgbColour[1] = 0;
      rgbColour[2] = 255;
      break;
    case 4:
      rgbColour[0] = 255;
      rgbColour[1] = 255;
      rgbColour[2] = 255;
      break;
    case 5:
      rgbColour[0] = 0;
      rgbColour[1] = 0;
      rgbColour[2] = 0;
      break;
  }
}
void handleReceivedTinyIRData(uint16_t aAddress, uint8_t aCommand, bool isRepeat) {
  if ((millis() - timer) > waitTillNextRead) {
    inputRemote = aCommand;
    Serial.print(aCommand);
    Serial.println();
    timer = millis();
  }
}

void completed() {
  analogWrite(RPin, 0);
  analogWrite(RPin, 0);
  analogWrite(RPin, 0);
  solved = 0;
  setColourRgb();

}

void patern() {
  switch (code) {
    case 0: arr[0] = 1; arr[1] = 3; arr[2] = 4; arr[3] = 2; arr[4] = 1; break;
    case 1: arr[0] = 2; arr[1] = 2; arr[2] = 4; arr[3] = 4; arr[4] = 1; break;
    case 2: arr[0] = 3; arr[1] = 2; arr[2] = 4; arr[3] = 4; arr[4] = 3; break;
    case 3: arr[0] = 1; arr[1] = 4; arr[2] = 2; arr[3] = 3; arr[4] = 2; break;
    case 4: arr[0] = 4; arr[1] = 2; arr[2] = 4; arr[3] = 3; arr[4] = 1; break;
    case 5: arr[0] = 3; arr[1] = 3; arr[2] = 4; arr[3] = 1; arr[4] = 2; break;
    case 6: arr[0] = 2; arr[1] = 1; arr[2] = 1; arr[3] = 4; arr[4] = 1; break;
    case 7: arr[0] = 1; arr[1] = 2; arr[2] = 3; arr[3] = 3; arr[4] = 4; break;
    case 8: arr[0] = 2; arr[1] = 3; arr[2] = 1; arr[3] = 4; arr[4] = 1; break;
    case 9: arr[0] = 4; arr[1] = 2; arr[2] = 4; arr[3] = 2; arr[4] = 1; break;
  }
}

void checkInput() {
  if (inputRemote > 0 && done) {
    delay(200);
    if (inputRemote - 3 == arr[ledcomp] && doneShowing) {
      showColor(inputRemote - 3);
      tone(buzzer, 1500);
      Serial.println("true");
      delay(100);
      noTone(buzzer);
      ledcomp++;
      timer = millis();
      if (ledcomp == ledcount) {
        ledcount++;
        ledcomp = 0;
        doneShowing = false;
      }
      if (ledcount == 6) {
        solved = 0;
      }
    } else {
      for (int i = 0; i <= 3; i++) {
        showColor(1);
        tone(buzzer, 3);
        delay(250);
        noTone(buzzer);
        showColor(5);
        delay(200);
      }
      ledcomp = 0;
      ledcount = 1;
      doneShowing = false;
      delay(2000);
    }
    inputRemote = 0;
  }
}

void checkGameOn() {
  if (inputRemote == 3 && done == false) {
    done = true;
    inputRemote = 0;
    doneShowing = false;
    timer = millis() + 2000;
    for (int i = 0; i < 5; i++) {
      Serial.print(arr[i]);
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
  patern();
  Serial.println(code);         // print the integer

}

void puzzleSolved() {
  Wire.write(solved);
}
