typedef unsigned char uint8_t;
const char *debModCom = "$$$\n";
const char *finModCom = "exit\n";
const char *setSsid = "set wlan ssid FreeWifi\n"; 
const char *setIp = "set ip a 10.42.0.200\n";
const char *setMask = "set ip netmask 255.255.255.0\n";
const char *ping = "Ping 10.42.0.1 10\n";
const char *joinSsid = "join FreeWifi\n";
const char *lites = "lites";
const char *enter = "\n"; 
const char *set = "set"; 
int byteSent;
char *buffer;

void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);
  byteSent=Serial1.write("$$$");
  delay(1000);
}

void loop(){      
Serial1.write("lites");
delay(10000);
}
