//#include <Audio.h>
#include <DAC.h>
#include <SD.h>
#include <SPI.h>
#include <Audio.h>
//#include <Can.h>

/* Premier programme pour vérifier 
le son capter sur entrée analogique 
et sortir le son sur un hp branché sur DAC0*/


int led1 = 10;
int led2 = 12;
int sensorValue1 = 0;  // variable pour récupérer les valeurs Echantillons
int hpPin = DAC0;    // Sortie audio
const int sonInPin = A0; // Entré audio


void setup() {

  // debug output at 9600 baud
  Serial.begin(9600);

  
  // initialize the digital pin as an output.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  //44100Khz car mono, 100ms de prebuff
  Audio.begin(44100, 100);
  pinMode(sonInPin, INPUT);
}



// the loop routine runs over and over again forever:
void loop() {
    //Lecture écriture sur 12bits
    analogReadResolution(12);
    analogWriteResolution(12);
    
    //Capture tension en entrée et conversion int sur 12bits
    sensorValue1 = analogRead(sonInPin);
    
    //Ecriture vers la pin DAC0(CNA) des valeurs récupéreées sur l'entrée analogique
    analogWrite(hpPin, sensorValue1);
}


/* transformation de la valeur int en short*/
short intVersShort(int entier){
  short s;
  s= (short) entier;
  return s;
}


/* fonction pour faire clignoter les leds rouge et verte en fonction des pics de son.*/
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




  
