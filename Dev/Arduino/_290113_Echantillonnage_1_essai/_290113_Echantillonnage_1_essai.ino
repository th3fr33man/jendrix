
#include <Scheduler.h>

const int Max = 1000;
const int Tampon = 100;
int *pEcr = 0;
int n=0;
int m=0;
const int sonInPin = A0; // Entré audio
int buffer[Max];
unsigned long var=0;



void setup(){
  
  Serial.begin(9600);              // debug output at 9600 baud
  Serial2.begin(115200);           //débit du port série 2 à 115200bauds/s pour un besoin de 44100 théoriques   
  pinMode(sonInPin, INPUT);        // Pin d'entrée analogique A0 configurée en "entrée"
}

void loop(){

    int static etat = 0;
    
    analogReadResolution(8);         // CAN écahntillonne le son sur 8 bits
    // analogWriteResolution(8);     // conf sortie CNA en prévue pour test 
    
    switch (etat){
                      
    case 0:
      if (micros()-var>=22){         // dès que temps écoulé est sup a 22 µs
        var=micros();                // on réinitialise var avec la nouvelle valeur de micros()
        etat=1;                      // on passe en état 1
      }
      break;
          
    case 1:                          // Début de lecture( avant tampon), seule l'écriture en mémoire est possible
      pEcr = buffer;                 // Le pointeur pEcr est associé au tableau buffer
      *pEcr=analogRead(sonInPin);    // Ecriture à l'adresse pEcr de l'échantillon lu   
      pEcr++;                        // Incrémentation du pointeur pour décaler l'écriture à la case suivante du tableau
      if (*pEcr==Tampon){            // Test pour voir si le tampon est remplis
        etat=3;                      // Si le tampon est remplis, passage à l'état 3
      }
      
      etat=0;                        // Si le tampon n'est pas encore remplis, retour à 0
    
    break;
    
    case 2:
      if (micros()-var>=22){         // si temps écoulées - var est sup a 22 µs
        var=micros();                // on réinitialise var
        etat=3;                      // on passe en état 1
      }
    break;
    
    case 3:    
      Serial2.println(buffer[n]);    // on envoie sur le port série l'échantillon stocké à l'adresse n
      n++;                           // incrémentation de n
      if (n==Max){                   // si l'on arrive au bout du tableau, on reprend la lecture au début 
          n=0;
      }
        etat=4;                      // une fois l'échantillon n envoyé sur le port série on passe à l'étape 4
    break;        
           
     case 4:
      *pEcr=analogRead(sonInPin);    // Ecriture l'échantillon issu du CAN à l'adresse *pECR
       m=int(pEcr);                  // "Cast" en int de la valeur de l'adresse pour permettre un test 
       if (m==Max){                  // si l'on arrive au bout du tableau, on reprend l'écriture à l'adresse "0" du tableau buffer 
         pEcr=buffer;
       }
       etat=2;                        // un fois l'écriture réalisée, on retourne au timer 2
      
     break;
    } 
      
}
