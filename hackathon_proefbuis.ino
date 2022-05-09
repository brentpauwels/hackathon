const int led = 12;
const int knop = 7;
int buttonState = 0; //de knop start niet ingedrukt
void setup() {
  pinMode(led,OUTPUT); //de led is output
  pinMode(knop,INPUT); //de knop is input
}

void loop() {
  digitalRead(buttonState);
  
  if (digitalRead(knop)==HIGH){ //de led gaat branden als de knop ingedrukt wordt.
    delay(1000); 
    if (digitalRead(knop)==HIGH){ // knop moet 1sec ingedrukt zijn om per ongeluk indrukken te proberen vermijden
      digitalWrite(led,HIGH);
    }
  }
}
