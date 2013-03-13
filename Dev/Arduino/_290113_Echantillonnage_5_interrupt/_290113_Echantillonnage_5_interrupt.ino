
#include <Scheduler.h>

const int Max = 100;    //1000
int *pEcr = 0;
int *pLec = 0;
char flag=0;
char flagEcr=0;
char flagLec=0;
const int sonInPin = A0; // Entré audio
int pin = 13;
volatile int state = LOW;
int buffer[Max];
unsigned long var=0;



void setup(){
  
  Serial.begin(9600);              // debug output at 9600 baud
  Serial2.begin(115200);           //débit du port série 2 à 115200bauds/s pour un besoin de 44100 théoriques   
  pinMode(sonInPin, INPUT);
  analogReadResolution(8);  
  pEcr=buffer;
  pLec=buffer;
  attachInterrupt(0,echantillonnage,CHANGE);
}

void loop(){
     
    if (pLec<pEcr){                    
    Serial2.println(*pLec);    
    pLec++;  
   }      
   else {
     if (flagEcr!=flagLec){                   
          Serial2.println(*pLec);
          pLec=buffer;
          flagLec=!flagLec;
    }  
    if (micros()-var>=22){         // 
      flag=1;
      var=micros(); 
      digitalWrite(pin,state);     
    }
   }
 }
  
 void echantillonnage(){
            
      *pEcr=analogRead(sonInPin);
      Serial.println(*pEcr);
      pEcr++;                        // Incrémentation du pointeur pour décaler l'écriture à la case suivante du tableau
      if (int(pEcr)==Max){            // Test pour voir si le tampon est remplis
        pEcr = buffer;                  // Si le tampon est remplis, passage à l'état 3
        flagEcr=!flagEcr;      
      }
      state = !state;     
}
