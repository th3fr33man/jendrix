
 
typedef unsigned char uint8_t;
const char *debModCom = "$$$\n";
const char *finModCom = "exit\n";
const char *setSsid = "set$wlan$ssid$test2\n"; 
const char *setIp = "set$ip$a$10.42.0.200\n";
const char *setMask = "set$ip$netmask$255.255.255.0\n";
const char *ping = "Ping$10.42.0.1$10\n";


const char *enter = "\n"; 
const char *set = "set"; 


SoftwareSerial WiFly = new SoftwareSerial(0, 1); // RX, TX


void setup(){
 Serial.begin(9600);
 Serial1.begin(9600);
 Serial2.begin(9600);
}


void loop(){      
  
  int etat = 0;
  case 0:
  SendCommand(debModCom);

 
  break;
 
  
  WiFly.println(debModCom);
  
  Serial.WiFly.read()
  
}
