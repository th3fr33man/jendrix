//#include <string.h>
 
typedef unsigned char uint8_t;
const char *debModCom = "$$$\n";
const char *finModCom = "exit\n";
const char *setSsid = "set wlan ssid FreeWifi\n"; 
const char *setIp = "set ip a 10.42.0.200\n";
const char *setMask = "set ip netmask 255.255.255.0\n";
const char *ping = "Ping 10.42.0.1 10\n";
const char *joinSsid = "join FreeWifi\n";

const char *enter = "\n"; 
const char *set = "set"; 
int byteSent;

char *buffer;


void setup(){
 Serial.begin(9600);
 Serial1.begin(9600);
 //Serial2.begin(9600);
 byteSent=Serial1.write(debModCom);
// Serial1.readBytes(buffer, strlen(buffer)) ;
//  Serial.println(buffer,BIN);

 //Serial.println(Serial.find("COM"));
  Serial.println("mode commande");
 Serial.println(byteSent);
 delay(1000);
 
 byteSent=Serial1.write(setSsid);
 Serial.println("ssid");
 Serial.println(byteSent);
 delay(1000);
 
 byteSent=Serial1.write(setIp);
 Serial.println("ip");
 Serial.println(byteSent);
 delay(1000);
 
 byteSent=Serial1.write(setMask);
 Serial.println("mask");
 Serial.println(byteSent);
 Serial1.write(joinSsid);
 byteSent=Serial1.write(finModCom);
 delay(1000);
 
 

}


void loop(){      
  
//  int etat = 0;
//  case 0:
//  SendCommand(debModCom);
//
// 
//  break;
 



 
 
 
 Serial.println("mode loop");
 Serial.println(Serial1.read());
 delay(1000);

  

  
}
