const int bouton = 10;  
int etatbouton=0;// Entrée bouton
int pin=13;
int i=0;
int j=0;
int k=0;
int m=0;
const int Max = 10000;    //1000
int *pRead = 0;
int *pPrint = 0;
boolean flag=0;
boolean flagRead=0;
boolean flagPrint=0;
const int sonInPin = A0;  // Entré audio

volatile int state = LOW;
int buffer[Max];
unsigned long var=0;
volatile boolean l;
char lsb;
char msb;
short Const=0;


//TC1 ch 0
void TC3_Handler()
{
        TC_GetStatus(TC1, 0);
        digitalWrite(13, l = !l); 
}

void startTimer(Tc *tc, uint32_t channel, IRQn_Type irq, uint32_t frequency) {
        pmc_set_writeprotect(false);
        pmc_enable_periph_clk((uint32_t)irq);
        TC_Configure(tc, channel, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);
        uint32_t rc = VARIANT_MCK/128/frequency; //128 because we selected TIMER_CLOCK4 above
        TC_SetRA(tc, channel, rc/2); //50% haut, 50% bas
        TC_SetRC(tc, channel, rc);
        TC_Start(tc, channel);
        tc->TC_CHANNEL[channel].TC_IER=TC_IER_CPCS;
        tc->TC_CHANNEL[channel].TC_IDR=~TC_IER_CPCS;
        NVIC_EnableIRQ(irq);
}

void setup(){
        
        Serial.begin(115200);
        
        pinMode(13,OUTPUT);
        pinMode(bouton,INPUT);
        startTimer(TC1, 0, TC3_IRQn, 11520); //TC1 channel 0, the IRQ for that channel and the desired frequency
        attachInterrupt(2,echantillonnage, CHANGE); 
        
        Serial2.begin(115200);           //débit du port série 2 à 115200bauds/s pour un besoin de 44100 théoriques   
        pinMode(sonInPin, INPUT);
         
        pRead=buffer+1000;
        pPrint=buffer;
       /*
        Serial2.println("auth dpac dpac");
        if Serial2.read()=="OK"{
         Serial2.println("wl-ssid AndroidAP");
          
      }
         Serial2.println("wl-type a");
         delay(2000);
         
          Serial2.println("wl-dhcp 1");
         delay(10000);
        
         Serial2.println("wl-chan 1");
         delay(1000);
                          
         Serial2.println("commit");
         delay(2000);
         
         Serial2.println("restart");
         delay(20000);
         
         Serial2.println("auth dpac dpac");
         delay(2000);
         Serial2.println("wl-tcp-ip 192.168.43.1");
         delay(2000);
         Serial2.println("pass");
         delay(2000);
        */
        
}

void loop(){
  
  
  //pour envoyer la commande "pass" au module dpac à l'aide de l'appui sur un bouton
//  etatbouton=digitalRead(bouton);
//  if (etatbouton==HIGH){
//    //Serial2.println("auth dpac dpac");
//    //delay(2000);
//    //
//    //Serial2.println("");
//    delay(2000);
//    Serial2.print("\n");
//    Serial2.print("pass\n");
//    delay(2000);
//  }
  
  
  if (int(pPrint)==Max+int(buffer)){
    pPrint=buffer;
  }
  
  
  //envoi des échantillon sur le port série (version 8bits)
  Serial2.write(*pPrint-127);
  pPrint++;
  
  
  //division des echantillons 16 bits en 2X8bits pour envoi sur port série(limité à 8bits)
//  lsb=(char)(*pPrint);                
//  Serial2.write(lsb);
//  //Serial.println(lsb);
//  msb=(char)(*pPrint>>8);
//  Serial2.write(msb);
//  //Serial.println(msb);
//  pPrint++;

}


// la fonction appelée par l'interruption externe n°0
void echantillonnage(){
  
  analogReadResolution(8);
  *pRead=/*Const*/ analogRead(sonInPin);                      
  
    if (int(pRead)==Max+int(buffer)){            
       pRead = buffer;
       //Const=0;
       //flagRead=!flagRead;
    } else {
      if (*pRead>125 && *pRead<129){
      *pRead=127;
      //Const++;
      }
     pRead++; 
    }    
 }

