#include <SPI.h>
typedef unsigned char uint8_t;

int slaveSelectPin = 10;
const char *debModCom = "$$$\n";
const char *finModCom = "exit\n";
const char *setSsid = "set$wlan$ssid$test2\n"; 
const char *setIp = "set$ip$a$10.42.0.200\n";
const char *setMask = "set$ip$netmask$255.255.255.0\n";
const char *ping = "Ping$10.42.0.1$10\n";
const char *enter = "\n"; 
const char *set = "set"; 
const char *rejoindre = "join$test3\n";
const char *lites = "lites\n";

void setup(){
 Serial.begin(9600);
 pinMode (slaveSelectPin, OUTPUT);
 SPI.begin(10);
 SPI.setDataMode();
 SPI.setClockDivider();
 SPI.setBitOrder();
}


void loop(){
 int static etat = 0;
   switch(etat){
   case 0:
     digitalWrite(slaveSelectPin,LOW);
     SendCommand(slaveSelectPin,debModCom);
     delay(1000);
     etat++;
   break;
   
   case 1:
     SendCommand(slaveSelectPin,lites);
     delay(10000);
   break;
   }
}


void SendCommand(int cs, const char *c ){
  int i = 0;
  for (i=0  ; i < strlen(c); i++){
  byte response = SPI.transfer(cs,(unsigned char)c[i],SPI_CONTINUE);
  Serial.println(c[i]);
  Serial.println((unsigned char)c[i]);
  Serial.println(response);
  //Serial.println(response);
  delay(10);
  }
}









//  
///*SPI.transfer(cs,byte,SPI_CONTINUE);*/
//byte response = 0;
//
// Serial.println(COM[0]);
// delay(1000);
//response = SPI.transfer(cs,'$',SPI_CONTINUE);
//Serial.println(response);
// delay(1000);
//response = SPI.transfer(cs, 0X24,SPI_CONTINUE);
//Serial.println(response);
// delay(1000);
//response = SPI.transfer(cs, 0x24,SPI_CONTINUE);
//Serial.println(response);
// delay(1000);
// 
// 
////get$mac 0x67 0x65 0x74 0x24 0x6D 0x61 0x63
//response = SPI.transfer(cs, 0x67,SPI_CONTINUE);
//Serial.println(response);
//response = SPI.transfer(cs, 0x65,SPI_CONTINUE);
//Serial.println(response);
//response = SPI.transfer(cs, 0x74,SPI_CONTINUE);
//Serial.println(response);
//response = SPI.transfer(cs, 0x24,SPI_CONTINUE);
//Serial.println(response);
//response = SPI.transfer(4, 0x6D,SPI_CONTINUE);
//Serial.println(response);
//response = SPI.transfer(4, 0x61,SPI_CONTINUE);
//Serial.println(response);
//response = SPI.transfer(4, 0x63,SPI_CONTINUE);
//Serial.println(response);
//}
// 

 
 
 
 
 
 
 
 
 
  /*SPI.transfer(cs,byte,SPI_CONTINUE);*/

 
 
 
// int etat = 0;
// switch(etat){
// case 0:
// *test = COM;
// test++;
// break;
// }

//}



//void stringVersUint8(String c){
//   *test = c;
//   stringVersUint8(COM);
//   Serial.println(test[1]);
//}



  
  
  

  

  
  
  
  



