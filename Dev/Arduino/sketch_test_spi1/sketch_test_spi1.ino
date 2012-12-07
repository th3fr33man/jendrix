#include <string.h>
//
//
//#define THR        0x00 << 3
//#define RHR        0x00 << 3
//#define IER        0x01 << 3
//#define FCR        0x02 << 3
//#define IIR        0x02 << 3
//#define LCR        0x03 << 3
//#define MCR        0x04 << 3
//#define LSR        0x05 << 3
//#define MSR        0x06 << 3
//#define SPR        0x07 << 3
//#define TXFIFO     0x08 << 3
//#define RXFIFO     0x09 << 3
//#define DLAB       0x80 << 3
//#define IODIR      0x0A << 3
//#define IOSTATE    0x0B << 3
//#define IOINTMSK   0x0C << 3
//#define IOCTRL     0x0E << 3
//#define EFCR       0x0F << 3
//////
//#define DLL        0x00 << 3
//#define DLM        0x01 << 3
//#define EFR        0x02 << 3
//#define XON1       0x04 << 3  
//#define XON2       0x05 << 3
//#define XOFF1      0x06 << 3
//#define XOFF2      0x07 << 3
//
////
////
//#define CS         SS
//#define MOSI       11
//#define MISO       12
//#define SCK        13
 #include <SoftwareSerial.h>
 //#include <SPI.h>
 typedef unsigned char uint8_t;

//const int cs = 10;
//const int mosi = 11;
//const int miso = 12;
//const int sck = 13;
//char ch="$";
const char *debModCom = "$$$\n";
const char *finModCom = "exit\n";
const char *setSsid = "set$wlan$ssid$test2\n"; 
const char *setIp = "set$ip$a$10.42.0.200\n";
const char *setMask = "set$ip$netmask$255.255.255.0\n";
const char *ping = "Ping$10.42.0.1$10\n";


const char *enter = "\n"; 
const char *set = "set"; 


//const uint8_t COM = "$$$\n";
uint8_t *test ;
SoftwareSerial WiFly(0, 1); // RX, TX

void setup(){
 Serial.begin(9600);
}


void loop(){
 int etat = 0;
 case 0:
   SendCommand(debModCom);

 
 break;
 




void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);
  mySerial.println("Hello, world?");
}

void loop() // run over and over
{
  if (mySerial.available())
    Serial.write(mySerial.read());
  if (Serial.available())
    mySerial.write(Serial.read());
}
 
 
 
 /*SendCommand(setSsid);
 SendCommand(setIp);
 SendCommand(setMask);
 SendCommand(finModCom);
 SendCommand(ping);
 */
}





void SendCommand(const char *c){
  int i = 0;
  for (i=0  ; i < strlen(c); i++){
  byte response = SPI.transfer(SS,(unsigned char)c[i]);
  Serial.print(c[i]);
  //Serial.println(response);
  delay(1000);
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



  
  
  

  

  
  
  
  



