int code = 176;



String Elements[] = {"Ca", "Na", "S", "H", "Cl", "Ni", "He", "B", "Hg", "Mg" };
int moeilijkheid;
long sDigit;
long lDigit;
short codeArr[10];

void setup() {
  Serial.begin(9600);
  moeilijkheid = (int)firstDigit(code);
  sDigit = codeGen(firstDigit(code - (moeilijkheid * 100)) + 1);
  lDigit = codeGen(lastDigit(code) + 1);
  codeCheck();

}

void loop() {

}
