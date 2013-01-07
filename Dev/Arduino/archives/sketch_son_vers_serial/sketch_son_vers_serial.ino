


const int MAX = 20;
int *pEcr = 0;
const int sonInPin = A0; // Entré audio
int buffer[MAX];

void setup() {
  // debug output at 9600 baud
  Serial.begin(9600);
  pinMode(sonInPin, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {

  int static etat = 0;
  
  switch (etat){
    case 0:
      //Lecture écriture sur 12bits
      analogReadResolution(12);
      analogWriteResolution(12);
      pEcr = buffer;
      etat++;
    break;
    
    case 1:
        //*pEcr = (int)analogRead(sonInPin);
        *pEcr=10;
        pEcr++;
        if (pEcr = buffer+MAX*4){
                  
          Serial.println("Debut");
            
          for (int i = 0 ; i< MAX ; i++){
            Serial.println(buffer[i]);
          }
          Serial.println("Fin");
          delay(1000);

        }
    break;
  }
  
  
}




/* transformation de la valeur int en short*/
short intVersShort(int entier){
  short s;
  s= (short) entier;
  return s;
}






  
