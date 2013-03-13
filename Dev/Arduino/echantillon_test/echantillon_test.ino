
#include <Scheduler.h>

const int Max = 1000;
const int Tampon = 100;
int *pEcr = 0;
int n=0;
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
                      //pEcr ppv l'adresse du tableau buffer 
    case 0:
      if (micros()-var>=22){               // si temps écoulées - var est sup a 22 µs
        var=micros();                      // on réinitialise var
        etat=1;                            // on passe en état 1
      }
      break;
          
    case 1:
      pEcr = buffer;    
      *pEcr=analogRead(sonInPin);       
      pEcr++;   
      if (*pEcr==Tampon){
        etat=3;                               // on repasse à l'état 0
      }
      
      etat 0;
    
      break;
    
    case 2:
      if (micros()-var>=22){               // si temps écoulées - var est sup a 22 µs
        var=micros();                      // on réinitialise var
        etat=1;                            // on passe en état 1
      }
      break;
    
    case 3:    
      Serial2.println=(buffer[n]);
      n++;   
      if (n==Max){
          n=0;
      }
        etat=4;                  
           
     case 4:
      *pEcr=analogRead(sonInPin);       
       
       if(pEcr==Max){
         pEcr=buffer;
       }
       etat 2;
      
     break;
      
      
}
