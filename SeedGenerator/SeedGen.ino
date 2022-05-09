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
  for (int y = moeilijkheid + 2; y >= 0; y--) {
    codeArr[count] = (lastDigit(sDigit / pow(10, y)));
    codeArr[count+moeilijkheid+2] = (lastDigit(lDigit / pow(10, y)));
    count++;
  }

//  for (int n: codeArr) {
//  Serial.print(n);
//  }
//  Serial.println("");
}
