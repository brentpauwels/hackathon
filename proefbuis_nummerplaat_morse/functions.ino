void A(){dot(); dash(); pauseTime();} //function for every char in Morse
void B(){dash(); dot(); dot(); dot(); pauseTime();}
void C(){dash(); dot(); dash(); dot(); pauseTime();}
void D(){dash(); dot(); dot(); pauseTime();}
void E(){dot(); pauseTime();}
void f(){dot(); dot(); dash(); dot(); pauseTime();}
void G(){dash(); dash(); dot(); pauseTime();}
void H(){dot(); dot();dot();dot();pauseTime();}
void I(){dot(); dot();pauseTime();}
void J(){dot(); dash();dash();dash();pauseTime();}
void K(){dash(); dot();dash();pauseTime();}
void L(){dot(); dash();dot();dot();pauseTime();}
void M(){dash();dash();pauseTime();}
void N(){dash();dot();pauseTime();}
void O(){dash();dash();dash();pauseTime();}
void P(){dot();dash();dash();dot();pauseTime();}
void Q(){dash();dash();dot();dash();pauseTime();}
void R(){dot();dash();dot();pauseTime();}
void S(){dot();dot();dot();pauseTime();}
void T(){dash();pauseTime();}
void U(){dot();dot();dash();pauseTime();}
void V(){dot();dot();dot();dash();pauseTime();}
void W(){dot();dash();dash();pauseTime();}
void X(){dash();dot();dot();dash();pauseTime();}
void Y(){dash();dot();dash();dash();pauseTime();}
void Z(){dash();dash();dot();dot();pauseTime();}
void one(){dot(); dash(); dash(); dash(); dash();}
void two(){dot(); dot(); dash(); dash(); dash();}
void three(){dot(); dot(); dot(); dash(); dash();}
void four(){dot(); dot(); dot(); dot(); dash();}
void five(){dot(); dot(); dot(); dot(); dot();}
void six(){dash(); dot(); dot(); dot(); dot();}
void seven(){dash(); dash(); dot(); dot(); dot();}
void eight(){dash(); dash(); dash(); dot(); dot();}
void nine(){dash(); dash(); dash(); dash(); dot();}
void zero(){dash(); dash(); dash(); dash(); dash();}


void convertToMorse(char inChar){
  if((inChar == 'A') || (inChar=='a')) A(); //no difference between shifted and unshifted chars
  else if((inChar == 'B') || (inChar=='b')) B(); 
  else if((inChar == 'C') || (inChar=='c')) C();  
  else if((inChar == 'D') || (inChar=='d')) D();
  else if((inChar == 'E') || (inChar=='e')) E();
  else if((inChar == 'F') || (inChar=='f')) f();
  else if((inChar == 'G') || (inChar=='g')) G();
  else if((inChar == 'H') || (inChar=='h')) H();
  else if((inChar == 'I') || (inChar=='i')) I();
  else if((inChar == 'J') || (inChar=='j')) J();
  else if((inChar == 'K') || (inChar=='k')) K();
  else if((inChar == 'L') || (inChar=='l')) L();
  else if((inChar == 'M') || (inChar=='m')) M();
  else if((inChar == 'N') || (inChar=='n')) N();
  else if((inChar == 'O') || (inChar=='o')) O();
  else if((inChar == 'P') || (inChar=='p')) P();
  else if((inChar == 'Q') || (inChar=='q')) Q();
  else if((inChar == 'R') || (inChar=='r')) R();
  else if((inChar == 'S') || (inChar=='r')) S();
  else if((inChar == 'T') || (inChar=='r')) T();
  else if((inChar == 'U') || (inChar=='r')) U();
  else if((inChar == 'V') || (inChar=='r')) V();
  else if((inChar == 'W') || (inChar=='w')) W();
  else if((inChar == 'X') || (inChar=='x')) X();
  else if((inChar == 'Y') || (inChar=='y')) Y();
  else if((inChar == 'Z') || (inChar=='z')) Z();
  else if(inChar == '1') one();  
  else if(inChar == '2') two();  
  else if(inChar == '3') three();  
  else if(inChar == '4') four();
  else if(inChar == '5') five();
  else if(inChar == '6') six();
  else if(inChar == '7') seven();
  else if(inChar == '8') eight();
  else if(inChar == '9') nine();
  else if(inChar == '0') zero();
}
