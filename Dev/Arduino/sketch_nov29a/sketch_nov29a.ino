//#include <Audio.h>
//#include <DAC.h>
#include <SD.h>
#include <SPI.h>
#include <Audio.h>

/* Premier programme pour vérifier 
le son capter sur entrée analogique 
et allumer les diodes en fonction
des tensions produites*/


int led1 = 10;
int led2 = 12;
int sensorValue1 = 0;
int hpPin = DAC0;
const int sonInPin = A0;


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  //pinMode(sonInPin, INPUT _ ANALOG)

  Audio.begin(44100, 100);
  //Serial.begin(9600);

  //pinMode(hpPin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  
  analogReadResolution(12); 
  analogWriteResolution(12);
  const int S = 4095;
  short buffer[];
  int volume = 1024;
  
  sensorValue1 = analogRead(sonInPin);
  sonEnCouleur(sensorValue1);
  
  //File myFile = sensorValue1;
  //buffer=sensorValue1;
  //Serial.print(sensorValue1);
  
  
  Audio.prepare(buffer, S, volume);
  Audio.write(buffer, S);
  
  //read(buffer, sizeof(buffer));
  
  //delay(10);
  
  //float voltage = sensorValue1 * (3.3 / 1023.0);

  //analogWrite(12, map(sensorVal, 0, 1023, 0, 4095));
}



void sonEnCouleur(int a){
  if (a>1900 && a<2100){
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  }
  else if (a>2100 || a<1900){
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  }
}




  
