int analogPin = A0;
bool opgelost = false;
bool goedeTemp = false;
unsigned long startOven = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(analogPin, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
  digitalWrite(13, LOW);
  digitalWrite(8, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  
      int val = analogRead(analogPin);
      //delay(250); 
        Serial.println(val);
        Serial.println(startOven);
        if(val <= 1024 && val >= 650){
          goedeTemp = true;
          Serial.println("goede temp");
        }else{
          startOven = 0;
          goedeTemp = false;
          Serial.println("slechte temp");
          digitalWrite(13, LOW);
          Serial.println(val);
        }
        if(startOven == 0 && goedeTemp){
            startOven = millis();
            Serial.println("start oven");
            digitalWrite(13, HIGH);
        }
    if(startOven !=0 && millis() >= startOven+6000){
            opgelost = true;
            Serial.println("vuur is langgenoeg warm");
            digitalWrite(8, HIGH);
    }
    
  
}
