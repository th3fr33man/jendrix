
#include <Scheduler.h>

const int Max = 1000;
const int Tampon = 100;
int *pEcr = 0;
const int sonInPin = A0; // Entré audio
int buffer[Max];
unsigned long var=0;



void setup(){
  // debug output at 9600 baud
  Serial.begin(9600);
  Serial2.begin(115200);
  pinMode(sonInPin, INPUT);
}

void loop(){

    int static etat = 0;
    
    analogReadResolution(8);                //Lecture écriture sur 8 bits
    // analogWriteResolution(8);
    
    switch (etat){
    case 0:
      pEcr = buffer;                       //pEcr ppv l'adresse du tableau buffer 
    
    case 1:
      if (micros()-var>=22){               // si temps écoulées - var est sup a 22 µs
        var=micros();                      // on réinitialise var
        etat=2;                            // on passe en état 1
      }
      break;
      
            
    case 2:
      pEcr+=Tampon;
      *pEcr=analogRead(sonInPin);       
      serial2.println(Buffer[pEcr-Tampon])
      pEcr++;   
      if (pEcr+Tampon==Max){
        etat=3;                               // on repasse à l'état 0
      }
      
      etat 1;
    
      break;
    
     case 3:
       pEcr=Tampon;
       
       etat 1;
      
     break;
      
      
}
