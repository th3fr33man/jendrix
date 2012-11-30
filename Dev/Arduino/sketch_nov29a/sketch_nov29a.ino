//#include <Audio.h>
//#include <DAC.h>

/* Premier programme pour vérifier 
le son capter sur entrée analogique 
et allumer les diodes en fonction
des tensions produites*/


int led1 = 10;
int led2 = 12;
int sensorValue1 = 0;
//int sensorValue2 = 0;
const int sonInPin = A0;


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
//sensorValue1 = analogRead(sonInPin);
  for (int i=0;i<1024;i++){
  sensorValue1 = i;
  sonEnCouleur(sensorValue1);
  delay(10);
  }
  
  
}



void sonEnCouleur(int a){
  if (a<512){
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  }
  else if (a>512){
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  }
}
  
