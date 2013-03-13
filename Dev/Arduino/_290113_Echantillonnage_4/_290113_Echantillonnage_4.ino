
#include <Scheduler.h>

const int Max = 100;    //1000
int *pEcr = 0;
int *pLec = 0;
char flagEcr=0;
char flagLec=0;
const int sonInPin = A0; // Entré audio
int buffer[Max];
unsigned long var=0;



void setup(){
  
  Serial.begin(9600);              // debug output at 9600 baud
  Serial2.begin(115200);           //débit du port série 2 à 115200bauds/s pour un besoin de 44100 théoriques   
  pinMode(sonInPin, INPUT);        // Pin d'entrée analogique A0 configurée en "entrée"
  Scheduler.startLoop(envoi_echantillons);
  pEcr=buffer;
  pLec=buffer;
  
}

void loop(){

    int static etat = 0;
    
    analogReadResolution(8);         // CAN écahntillonne le son sur 8 bits
    // analogWriteResolution(8);     // conf sortie CNA en prévue pour test 
    
    switch (etat){
                      
    case 0:
      //if (micros()-var>=22){         // dès que temps écoulé est sup a 22 µs
      //var=micros();                // on réinitialise var avec la nouvelle valeur de micros()
       delayMicroseconds(220);
        etat=1;                      // on passe en état 1
      //}
      
      break;
          
    case 1:                          // Début de lecture( avant tampon), seule l'écriture en mémoire est possible
      
      *pEcr=analogRead(sonInPin);
      //Serial.println("ecriture");
      Serial.println(*pEcr);    // Ecriture à l'adresse pEcr de l'échantillon lu   
      pEcr++;                        // Incrémentation du pointeur pour décaler l'écriture à la case suivante du tableau
      if (int(pEcr)==Max){            // Test pour voir si le tampon est remplis
        pEcr = buffer;                  // Si le tampon est remplis, passage à l'état 3
        flagEcr=!flagEcr;      
      }
      
      etat=0;                        // Si le tampon n'est pas encore remplis, retour à 0
    
    break;
    }  
}
  // Boucle d'envoi du son sur RS232
  
 void envoi_echantillons(){
       
    int static tampon = 0;
    
    //analogReadResolution(8);         // CAN écahntillonne le son sur 8 bits
    // analogWriteResolution(8);     // conf sortie CNA en prévue pour test 
    
   if (pLec<pEcr){                    
    Serial2.println(*pLec);    // on envoie sur le port série l'échantillon stocké à l'adresse n
    //Serial.println("lecture");
    //Serial.println(*pLec);
      pLec++;  
   }      // incrémentation de n
   else {
     if (flagEcr!=flagLec){                   // si l'on arrive au bout du tableau, on reprend la lecture au début 
          Serial2.println(*pLec);
          //Serial.println("lecture décalée");
          pLec=buffer;
          flagLec=!flagLec;
      }
   }
    yield();       
}
