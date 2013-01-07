//**************************************************************//
//  Name    : shiftOutCode, Hello World                         //
//  Author  : Carlyn Maw,Tom Igoe                               //
//  Date    : 25 Oct, 2006                                      //
//  Version : 1.0                                               //
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                            //
//****************************************************************
const char *debModCom = "$$$\n";
const char *lites = "lites\n";
int latchPin = 10;
int clockPin = 13;
int dataPin = 11;

#include "WiFly.h"
void setup() {
  //set pins to output because they are addressed in the main loop
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  SpiSerial.begin();
}

void loop() {
  //count up routine
  int static etat = 0;
      Serial.println("debut loop");

   switch(etat){
  case 0:
    Serial.println("Case0");

    for (int j = 0; j < strlen(debModCom); j++) {
      //ground latchPin and hold low for as long as you are transmitting
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, debModCom[j]);  
      //return the latch pin high to signal chip that it
      //no longer needs to listen for information
      digitalWrite(latchPin, HIGH);
      delay(1000);
    }
    etat++;
  break;
   
  case 1:
  Serial.println("Case1");
    for (int j = 0; j < strlen(lites); j++) {
      //ground latchPin and hold low for as long as you are transmitting
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, lites[j]);  
      //return the latch pin high to signal chip that it
      //no longer needs to listen for information
      digitalWrite(latchPin, HIGH);
      delay(1000);
    }
  break;
  }
}


//void SendCommand(const char *c){
//  int i = 0;
//  for (i=0  ; i < strlen(c); i++){
//  byte response = SPI.transfer(SS,(unsigned char)c[i],SPI_CONTINUE);
//  Serial.print(c[i]);
//  //Serial.println(response);
//  delay(10);
//  }
//}
