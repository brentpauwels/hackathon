
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
  for (int i = 0; i <= 1000; i++) {
    for (int x = 0; x <= 255; x++) {
      analogWrite(RPin, x);
      delay(1);
    }
    for (int y = 255; y >= 0; y--) {
      analogWrite(BPin, y);
      delay(1);
    }
    for (int i = 0; i <= 255; i++) {
      analogWrite(GPin, i);
      delay(1);
    }
    for (int y = 255; y >= 0; y--) {
      analogWrite(RPin, y);
      delay(1);
    }
    for (int z = 0; z <= 255; z++) {
      analogWrite(BPin, z);
      delay(1);
    }
    for (int y = 255; y >= 0; y--) {
      analogWrite(GPin, y);
      delay(1);
    }
  }
}
