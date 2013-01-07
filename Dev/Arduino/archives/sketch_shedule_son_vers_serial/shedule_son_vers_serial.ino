
#include <Scheduler.h>

const int MAX = 20;
int *pEcr = 0;
const int sonInPin = A0; // Entré audio
int buffer[MAX];

void setup() {
  // debug output at 9600 baud
  Serial.begin(9600);
  pinMode(sonInPin, INPUT);
  Scheduler.startLoop(loop1);
}

// the loop routine runs over and over again forever:
/* 1ere boucle pour initialiser le pointeur pEcr vers le buffer */
void loop() { 
      //Lecture écriture sur 12bits
      Serial.println("loop"); 
      analogReadResolution(12);
      analogWriteResolution(12);
      pEcr = buffer;
      yield();
}


/* 2eme boucle pour inscrire les données dans le buffer */
void loop1() {
        Serial.println("loop1"); 
        *pEcr=10;
        pEcr++;
        if (pEcr == buffer+MAX){    
          Serial.println("Debut"); 
          for (int i = 0 ; i< MAX ; i++){
            Serial.println(buffer[i]);
          }
          Serial.println("Fin");
          yield();
        }
    
}



/* transformation de la valeur int en short*/
short intVersShort(int entier){
  short s;
  s= (short) entier;
  return s;
}

