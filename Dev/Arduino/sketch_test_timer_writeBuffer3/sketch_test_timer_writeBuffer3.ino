
#include <Scheduler.h>

const int MAX = 10;
int *pEcr = 0;
const int sonInPin = A0; // Entré audio
int buffer[MAX];
unsigned long var=0;

void setup() {
  // debug output at 9600 baud
  Serial.begin(9600);
  Serial1.begin(115200);
  pinMode(sonInPin, INPUT);
}



void loop(){

    int static etat = 0;
    //Serial.println("loop");
    //Lecture écriture sur 12bits
    analogReadResolution(12);
    analogWriteResolution(12);
    
    switch (etat){
    case 0:
      pEcr = buffer;                       //pEcr ppv l'adresse du tableau buffer 
      if (millis()-var>=1000){             // si temps écoulées - var est sup a 1000 ms
        var+=1000;                         // on incrémente var de 1000 ms
        Serial.println(var);               // on imprime à l'écran la valeur de var et  
        Serial.println(millis());          // la valeur du temps écoulé en réel pour comparer
        etat=1;                            // on passe en état 1
      }
      break;
      
      case 1:
      //Serial.println("case1");          
      *pEcr=analogRead(sonInPin);          // on stock dans buffer case 0 la valeur de la lecture
      pEcr++;                              // on incremente l'adresse
      if (pEcr == buffer+MAX){             // si on arrive en vout de buffer on passe à l'état 2
        etat=2;
      }
      
      break;
      
      
      case 2:
         Serial.println("debut");               // test pour debug
         for (int i = 0 ; i< MAX ; i++){
          Serial.println(buffer[i]);
          Serial1.println(buffer[i]);
         }
       Serial.println("Fin");
       etat=0;                                 // on repasse à l'état 0
      
      break;
    }
  
}
