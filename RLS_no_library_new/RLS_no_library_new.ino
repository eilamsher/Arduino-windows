//#include <WireS.h>
#include "WireS.h"  
//#include <SoftwareSerial.h>
//#include <Wire.h>


#define PPR17 131072.0    // 17Bits 2^17
#define PPR18 262144.0    // 18Bits 2^18
#define RX    11   // *** D3, Pin 2
#define TX    12   // *** D4, Pin 3


#define Serial2   Serial
#define Wire   TinyWireS
//SoftwareSerial mySerial(RX, TX);

//=====[ Constants ]============================================================
#define address 44

//=====[ VARIABLES ]============================================================
int bau = 57600;
float enc1_val;
unsigned int val;
byte a;
byte b;

//=====[ FUNCTIONS ]============================================================
void begin(long baudRate) {
  Serial2.begin(baudRate);
//  while (!Serial2);
  //Serial.begin(baudRate);
  //while(!Serial);
  //Serial.println("-->Encoder Started.");
}

void get_status() {
  Serial2.flush();
  Serial2.write(0x69); delay(5);
  byte b1 = Serial2.read();
  byte b2 = Serial2.read();
//  Serial.print("--> Encoder status: ");
//  Serial.print(b1, HEX);
//  Serial.print(":");
//  Serial.print(b2);
//  Serial.println(";");
}


void set_baud(long baudRate, byte dir) {
  byte b[4];
  b[0] = (baudRate & 0xFF); //extract first byte
  b[1] = ((baudRate >> 8) & 0xFF); //extract second byte
  b[2] = ((baudRate >> 16) & 0xFF); //extract third byte
  b[3] = ((baudRate >> 24) & 0xFF); //extract fourth byte
  Serial2.flush();
  unlock();
  Serial2.write(0x42); delay(5);

  if (dir) {
    for (int i = 0; i < 4; i++) {
      Serial2.write(b[i]);
      delay(5);

    }
  }
  else {
    for (int i = 3; i >= 0; i--) {
      Serial2.write(b[i]);
      delay(5);
    }
  }
  delay(10);
  save_conf(); delay(10);
}

/*
void set_zero() {
  unlock();
  Serial2.write(0x5A); delay(5);
  Serial2.write(0xFF); delay(5);
  Serial2.write(0x00); delay(5);
  Serial2.write(0x00); delay(5);
  Serial2.write(0xFF); delay(5);
  save_conf(); delay(10);
//  Serial.println("--> Encoder zero set");

}*/

void unlock() {
  Serial2.write(0xCD); delay(5);
  Serial2.write(0xEF); delay(5);
  Serial2.write(0x89); delay(5);
  Serial2.write(0xAB); delay(5);
//  Serial.println("--> Encoder unlock");
}

/*
void set_read() {
  unlock();
  Serial2.write(0x54); delay(5);    // Continues Read = 'T'
  Serial2.write(0x01); delay(5);    // Auto-start enable = 1
  Serial2.write(0x33); delay(5);    // Short response = '3'
  Serial2.write(0x00); delay(5);    // Period (250 micro-sec) (byte 8)
  Serial2.write(0xFA); delay(5);    // Period (250 micro-sec) (byte 9)
//  Serial.println("--> Encoder Set to Continues read mode '1'.\n\tDont forget to start using 'start_response()'");
  save_conf();
  //get_status();
}*/

void start_response() {
  //unlock();
  Serial2.write(0x53); delay(5);    // Continues Read = 'S'
//  Serial.println("--> Encoder Set to start continues read.");
  save_conf();
  //get_status();
}

float get_pos() {
  byte b1 = Serial2.read();
  byte b2 = Serial2.read();
  byte b3 = Serial2.read();
  uint32_t pos = b3 + (b2 << 8) + (b1 << 16);

  pos = (pos >> 7);
  float pos_ang = pos * 360.0 / PPR17;
  return pos_ang;
}

uint32_t get_raw_data() {
  byte b1 = Serial2.read();
  byte b2 = Serial2.read();
  byte b3 = Serial2.read();
  uint32_t pos = b3 + (b2 << 8) + (b1 << 16);
  return (pos >> 7);
}

void save_conf() {
  unlock();
  Serial2.write(0x63); delay(5);    // save configuration parameters = 'c'
//  Serial.println("--> Encoders Configurations saved.\nYou have to reset the Encoder.");
}


//=====[ SETUP ]================================================================
void setup() {
  Wire.begin(address);      
  Wire.onRequest(requestEvent); 
  //Serial.begin(bau); while (!Serial);
  //begin(bau * 2);
  delay(5);
  //set_zero();
  delay(5);
  //set_baud(bau, 0);
  delay(5);

  begin(30700);
  delay(5);

}

//=====[ LOOP ]=================================================================
void loop() {


  Serial2.flush();
  while (Serial2.available()) {
    enc1_val = get_pos();
    //if (enc1_val > 180.0)
    //  enc1_val -= 360.0;
    break;
  }
  val = 100 * abs(enc1_val);
  a = val / 100;
  b = val % 100;
  //Serial.print("val : ");            // uncomment this for printing
  //Serial.println(enc1_val, 2);           // uncomment this for printing
  delay(5);
}
//==============================================================================

void requestEvent()
{
  Wire.write(a);     // respond with message of 1 bytes
  Wire.write(b);     // respond with message of 1 bytes

}
