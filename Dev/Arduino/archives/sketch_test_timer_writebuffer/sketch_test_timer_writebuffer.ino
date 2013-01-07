
#include <Scheduler.h>

const int MAX = 20;
int *pEcr = 0;
const int sonInPin = A0; // Entré audio
int buffer[MAX];
unsigned long var=0;

void setup() {
  // debug output at 9600 baud
  Serial.begin(9600);
  pinMode(sonInPin, INPUT);
  Scheduler.startLoop(loop1);
  //Scheduler.startLoop(loop2);
}



void loop(){

  //Lecture écriture sur 12bits

  analogReadResolution(12);
  analogWriteResolution(12);
  pEcr = buffer;
     
  Serial.println("loop");
  if (millis()+var>=var+100){
    var+=millis();
    Serial.println(var);
    yield();
  }
}
  

  


/* 2ere boucle pour initialiser le pointeur pEcr vers le buffer */
//void loop1() { 
//      //Lecture écriture sur 12bits
//      Serial.println("loop1"); 
//      analogReadResolution(12);
//      analogWriteResolution(12);
//      pEcr = buffer;
//      yield();
//}


/* 3eme boucle pour inscrire les données dans le buffer */
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

