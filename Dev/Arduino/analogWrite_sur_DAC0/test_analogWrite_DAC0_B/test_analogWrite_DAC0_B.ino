//#include <Audio.h>
//#include <DAC.h>
//#include <SD.h>
//#include <SPI.h>
#include <Audio.h>
//#include <Can.h>

/* Premier programme pour vérifier 
le son capter sur entrée analogique 
et allumer les diodes en fonction
des tensions produites*/


int led1 = 10;
int led2 = 12;
const int S=1024;         // Number of samples to read in block
short sensorValue1[S];    // variable pour récupérer les valeurs Echantillons
int hpPin = DAC1;         // Sortie audio
const int sonInPin = A0;  // Entré audio
int i = 0;

  //the setup routine runs once when you press reset:
void setup() {

  //debug output at 9600 baud
  Serial.begin(9600);

  
  // initialize the digital pin as an output.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  //44100Khz car mono, 100ms de prebuff
  Audio.begin(44100, 1000);                      //nécéssaire pour initialiser la sortie DAC
  pinMode(sonInPin, INPUT);
}



// the loop routine runs over and over again forever:
void loop() {
    
    int count =0;
    analogReadResolution(12);
    analogWriteResolution(12);
    //Audio.buffer = intVersShort(analogRead(sonInPin));
    Audio.buffer = analogRead(sonInPin);

    //sensorValue1[i] 
    i++;        
    if (i=1023){i=0;}
              

    
    
    
    //short buffer[S];
    int volume = 1024;
    Audio.prepare(Audio.buffer, S, volume);
    Audio.write(Audio.buffer,S);


    //analogWrite(hpPin, shortVersInt(sensorValue1[i]));

     
}


/* transformation de la valeur int en short*/
short intVersShort(int entier){
  short s;
  s= (short) entier;
  return s;
}


int shortVersInt(short court){
 int i;
 i = (int) court;
  return i;
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




  
