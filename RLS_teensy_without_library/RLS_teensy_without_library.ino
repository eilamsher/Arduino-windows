//#include "RLS_Encoder.h"
#include <SoftwareSerial.h>

#define PPR17 131072.0    // 17Bits 2^17
#define PPR18 262144.0    // 18Bits 2^18
#define baudRate 115200    // 
#define RX    3   // *** D3, Pin 2
#define TX    4   // *** D4, Pin 3


//#define mySerial    Serial2
//SoftwareSerial mySerial(RX, TX);
/*
  union u_tag{
    byte b[4];
    float fval;
  } u;
*/
//=====[ VARIABLES ]============================================================

//RLS_Encoder enc;

byte data[4] = {0};
//int value = 0;
float enc1_val;

//=====[ SETUP ]================================================================
void setup() {
  Serial.begin(9600); while (!Serial);
  //Serial.println("Start");
  //enc.begin();
  RLS_begin();
  //enc.set_read();
  //RLS_set_read();
}

//=====[ LOOP ]=================================================================
void loop() {

  // Read first=this encoder position
  Serial2.flush();
  while (Serial2.available()) {
    //if (Serial2.read()=='1'){
    enc1_val = RLS_get_pos();
    if (enc1_val > 180.0)
      enc1_val -= 360.0;
    break;
  }
  Serial.print("val ; ");            // uncomment this for printing
  Serial.println(enc1_val);            // uncomment this for printing
  delay(500);
}
//==============================================================================

void RLS_begin() {
  Serial2.begin(115200);
  while (!Serial2);
  Serial.println("-->Encoder Started.");
}

void RLS_set_read() {
  RLS_unlock();
  Serial2.print(0x54); delay(5);    // Continues Read = 'T'
  Serial2.print(0x01); delay(5);    // Auto-start enable = 1
  Serial2.print(0x33); delay(5);    // Short response = '3'
  Serial2.print(0x00); delay(5);    // Period (250 micro-sec) (byte 8)
  Serial2.print(0xFA); delay(5);    // Period (250 micro-sec) (byte 9)
  Serial.println("--> Encoder Set to Continues read mode '1'.\n\tDont forget to start using 'start_response()'");
  RLS_save_conf();
  //RLS_Encoder::get_status();
}


void RLS_unlock() {
  Serial2.print(0xCD); delay(5);
  Serial2.print(0xEF); delay(5);
  Serial2.print(0x89); delay(5);
  Serial2.print(0xAB); delay(5);
}

float RLS_get_pos() {
  byte b1 = Serial2.read();
  byte b2 = Serial2.read();
  byte b3 = Serial2.read();
  uint32_t pos = b3 + (b2 << 8) + (b1 << 16);

  pos = (pos >> 7);
  float pos_ang = pos * 360.0 / PPR17;
  return pos_ang;
}

void RLS_save_conf() {
  RLS_unlock();
  Serial2.print(0x63); delay(5);    // save configuration parameters = 'c'
  Serial.println("--> Encoders Configurations saved.\nYou have to reset the Encoder.");
}
