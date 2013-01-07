//---include area

#include <SPI.h>
#include "WiFly.h"
#include "Credentials.h"

//---variable declaration

//ethernet card related
byte server[] = { 192, 168, 1, 24 }; // Write server IP address here
Client client(server, 6000); //connect to this port on the server and send local IP address
Client client2(server, 8080); //connect to this port on the server to receive stream

unsigned char data0;

//** Ethernet chip pin assignment
#define ETHER_CS 10

/** Control Chip Select Pin (for accessing SPI Control/Status registers) */
#define MP3_XCS 6

/** Data Chip Select / BSYNC Pin */
#define MP3_XDCS 7

//** Data Request Pin: Player asks for more data */
#define MP3_DREQ 2
#define MP3_RST 8
/** VS10xx SCI Registers */
#define SPI_MODE 0x0   /**< VS10xx register */
#define SPI_STATUS 0x1   /**< VS10xx register */
//#define SPI_BASS 0x2   /**< VS10xx register */
#define SPI_CLOCKF 0x3   /**< VS10xx register */
//#define SPI_DECODE_TIME 0x4   /**< VS10xx register */
#define SPI_AUDATA 0x5   /**< VS10xx register */
//#define SPI_WRAM 0x6   /**< VS10xx register */
//#define SPI_WRAMADDR 0x7   /**< VS10xx register */
//#define SPI_HDAT0 0x8   /**< VS10xx register */
//#define SPI_HDAT1 0x9   /**< VS10xx register */
//#define SPI_AIADDR 0xa   /**< VS10xx register */
#define SPI_VOL 0xb   /**< VS10xx register */
//#define SPI_AICTRL0 0xc   /**< VS10xx register */
//#define SPI_AICTRL1 0xd   /**< VS10xx register */
//#define SPI_AICTRL2 0xe   /**< VS10xx register */
//#define SPI_AICTRL3 0xf   /**< VS10xx register */

//---functions area

//ethernet card related
//enable the ethernet chip on the SPI bus
void EtherSelect(){
  digitalWrite(ETHER_CS, LOW);
}

//disable the ethernet chip on the SPI bus
void EtherDeselect(){
  digitalWrite(ETHER_CS, HIGH);
}

//mp3 card related
unsigned char SPIGetChar(){
  unsigned char returned = SPI.transfer(0xFF);
  return returned; /* Return the received byte */
}

/** Pull the VS10xx Control Chip Select line Low */
void Mp3SelectControl(){
  digitalWrite(MP3_XCS, LOW);
}

/** Pull the VS10xx Control Chip Select line High */
void Mp3DeselectControl(){
  digitalWrite(MP3_XCS, HIGH);
}

/** Pull the VS10xx Data Chip Select line Low */
void Mp3SelectData(){
  digitalWrite(MP3_XDCS, LOW);
}

/** Pull the VS10xx Data Chip Select line High */
void Mp3DeselectData(){
  digitalWrite(MP3_XDCS, HIGH);
}

void SPIWait(){
  while (!digitalRead(MP3_DREQ)){}; 
}

/** Write VS10xx register */
void Mp3WriteRegister(unsigned char addressbyte, unsigned char highbyte, unsigned char lowbyte){
  Mp3DeselectData();
  Mp3SelectControl();
  delay(1);
  SPI.transfer(0x02);  //write command
  SPI.transfer(addressbyte);
  SPI.transfer(highbyte);
  SPI.transfer(lowbyte);
  SPIWait();
  Mp3DeselectControl();
}

/** Set VS10xx Volume Register */
void Mp3SetVolume(unsigned char leftchannel, unsigned char rightchannel){
  Mp3WriteRegister(SPI_VOL,leftchannel,rightchannel);
}

void InitMicrocontroller(){
  //SPI.setClockDivider(SPI_CLOCK_DIV64);//slow SPI bus speed
  SPI.setClockDivider(255);
  SPI.transfer(0xFF);
}

void SPIInit(){
  //max SDI clock freq = CLKI/7 and (datasheet) CLKI = 36.864, hence max clock = 5MHz
  //SPI clock arduino = 16MHz. 16/ 4 = 4MHz -- ok!
  SPI.setClockDivider(21);
}

/** Soft Reset of VS10xx (Between songs) */
void Mp3SoftReset(){
  InitMicrocontroller();
  Mp3WriteRegister (SPI_MODE, 0x08, 0x44);
  /* Newmode, Reset, No L1-2, stream enabled */
  delay(1); /* One millisecond delay */
  SPIWait();
  /* Set clock register, doubler etc. */
  Mp3WriteRegister(SPI_CLOCKF, 0x88, 0x00);
  delay(1); /* One millisecond delay */
  SPIWait();
  SPIInit();         
  Mp3SetVolume(0xff,0xff); //Declick: Immediately switch analog off
  /* Declick: Slow sample rate for slow analog part startup */
  Mp3WriteRegister(SPI_AUDATA, 0, 10); /* 10 Hz */
  delay(100);
  /* Switch on the analog parts */
  Mp3SetVolume(0xfe,0xfe);
  Mp3WriteRegister (SPI_AUDATA, 0xAC, 0x45);//stereo, 44100KHz sampling
  Mp3SetVolume(20,20); // Set initial volume (20 = -10dB)             
}

//---pin and cards initialization - setup()
void setup()
{
  Serial.begin(115200);
  Serial.println("Initializing...");
 
  pinMode(MP3_DREQ, INPUT);
  pinMode(MP3_XCS, OUTPUT);
  pinMode(MP3_XDCS, OUTPUT);
  pinMode(ETHER_CS, OUTPUT); 
  pinMode(MP3_RST, OUTPUT);
  digitalWrite(MP3_RST, HIGH);
  digitalWrite(MP3_XCS, HIGH);
  digitalWrite(MP3_XDCS, HIGH);
   
  WiFly.begin();
  SPI.begin();
 
  if (!WiFly.join(ssid)) {
    Serial.println("Association failed. Shield needs a reset.");
    while (1) {
     
      // Hang on failure.
    }
  }
  Serial.print("IP: ");
  Serial.println(WiFly.ip());

  Mp3SoftReset();
 
  delay(500);
}

//---main - loop()
void loop(){
  char c ='0'; 
  EtherSelect();
  if (client.connect()){
    client.flush();
    delay(100);   
    client.println("10.0.0.2");   
    delay(200);
    c = client.read();
    delay(100);
    //c = client.read();
    //delay(100);
    Serial.println(c);
    client.println("bye");
    delay(200);
    client.stop();
    delay(100);
  }
  else Serial.println("Connection to port 6000 is not available!");
  EtherDeselect();
 
  switch (c){
 
    case 'p':
      //what to do if server is asking client to play the stream:
     
        EtherDeselect();
        Mp3SoftReset();
        EtherSelect();
     
        if (client2.connect()){
          delay(10);
          Serial.println("Connected to data transfer port!");
          client2.println("GET / HTTP/1.1");
          client2.println();client2.println();
          delay(1);
         
          while (client2.connected()){
            EtherSelect();
            data0 = client2.read();
            EtherDeselect();
            SPIWait();
            Mp3SelectData();
            SPI.transfer(data0);
            delay(1);
            Mp3DeselectData();       
          }
         
        //shutdown Ethernet
        client2.flush();
        client2.stop();       
        EtherDeselect();
        /*****************************************/       
        //Shutdown player
        Mp3SelectData();
        for (int i=0; i<2048; i++) {
          while (!digitalRead(MP3_DREQ)); // wait here until DREQ is high again
          SPI.transfer(0x00);     
        }
        SPIWait(); // Wait until SPI transfer is completed
        Mp3DeselectData();             
        /*****************************************/
        EtherSelect();       
      }
      else Serial.println("Failed connection to streaming server!");
      Serial.println("Status 1");   
    break;
 
    case 'n':
      //what to do if server is asking for client not to play the stream
      Serial.println("Status 2");
    break;
 
    default:
      //what to do in all other commands (faulty) sent by server
    Serial.println("Status 3");
  }
}
