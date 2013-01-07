
#include <Scheduler.h>

const int MAX = 10;
int *pEcr = 0;
const int sonInPin = A0; // Entré audio
int buffer[MAX];
unsigned long var=0;

void setup() {
  // debug output at 9600 baud
  Serial.begin(9600);
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
      pEcr = buffer;
      //Serial.println("case0");
      if (millis()-var>=1000){
        var+=1000;
        Serial.println(var);
        Serial.println(millis());
        etat=1;
      }
      break;
      
      case 1:
      //Serial.println("case1");
      *pEcr=analogRead(sonInPin);
      pEcr++;
      if (pEcr == buffer+MAX){
        etat=2;
      }
      
      break;
      
      
      case 2:
         Serial.println("debut"); 
         for (int i = 0 ; i< MAX ; i++){
          Serial.println(buffer[i]);
         }
       Serial.println("Fin");
       etat=0;
      
      break;
    }
  
}
