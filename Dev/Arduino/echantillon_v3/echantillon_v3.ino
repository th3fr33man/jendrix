
#include <Scheduler.h>

const int MAX = 1000;
int *pEcr = 0;
const int sonInPin = A0; // Entré audio
int buffer[MAX];
unsigned long var=0;
unsigned long stockVar[MAX];
unsigned long stockMicros[MAX];
unsigned long timer=0;
int j=0;


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
      if (micros()-var>=22){               // si temps écoulées - var est sup a 23 µs
                                  // on incrémente var de 23 µs
        Serial.println(var);               // on imprime à l'écran la valeur de var et  
        Serial.println(micros());          // la valeur du temps écoulé en réel pour comparer
        var=micros(); 
        etat=1;                            // on passe en état 1
      }
      break;
      
      case 1:                               //Serial.println("case1");          
      *pEcr=analogRead(sonInPin);          // on stock dans buffer case 0 la valeur de la lecture
      //stockVar[j]=var;
      //timer = micros();
      //stockMicros[j]=timer;
      //j++;
      pEcr++;                              // on incremente l'adresse
      if (pEcr == buffer+MAX){             // si on arrive en bout de buffer on passe à l'état 2
        etat=2;
      }
      
      break;
      
      
      case 2:
         //Serial.println("debut");            // test pour debug
         //for (int i = 0 ; i< MAX ; i++){
           //Serial.println(stockVar[i]);
           //Serial.println(stockMicros[i]);
         //}
       Serial2.println("Fin");
       etat=0;                               // on repasse à l'état 0
      
      break;
    }
  
}
