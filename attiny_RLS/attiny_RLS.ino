#include "TinyWireS.h"                  // wrapper class for I2C slave routines
#include <SoftwareSerial.h>
#define address  0x8            // i2c slave address (38)
#define PPR17 131072.0    // 17Bits 2^17
#define PPR18 262144.0    // 18Bits 2^18
#define RX    3   // *** D3, Pin 2
#define TX    4   // *** D4, Pin 3

SoftwareSerial mySerial(RX, TX);


byte data[4]={0};
//int value = 0;
float enc1_val;



void requestEvent()
{
  TinyWireS.send(5);
  /*
  for (int i = 7; i >= 0; i--) {
    TinyWireS.send(data[i]);
  }
  */
}

void setup()
{
  TinyWireS.begin(address);      // init I2C Slave mode
  TinyWireS.onRequest(requestEvent);
  

  
}

void loop()
{
  mySerial.flush();
  while (mySerial.available()){
      //if (mySerial.read()=='1'){
        enc1_val = RLS_get_pos();
        if (enc1_val > 180.0)
          enc1_val -=360.0;
        break;
    }
}










void RLS_begin(){
  mySerial.begin(115200);
  while(!mySerial);
  //Serial.begin(baudRate);
  //while(!Serial);
  //Serial.println("-->Encoder Started.");
}


void RLS_set_read(){
  RLS_unlock();
  mySerial.write(0x54); delay(5);    // Continues Read = 'T'
  mySerial.write(0x01); delay(5);    // Auto-start enable = 1
  mySerial.write(0x33); delay(5);    // Short response = '3'
  mySerial.write(0x00); delay(5);    // Period (250 micro-sec) (byte 8)
  mySerial.write(0xFA); delay(5);    // Period (250 micro-sec) (byte 9)
  //Serial.println("--> Encoder Set to Continues read mode '1'.\n\tDont forget to start using 'start_response()'");
  RLS_save_conf();
  //RLS_Encoder::get_status();
}


void RLS_unlock(){
  mySerial.write(0xCD); delay(5);
  mySerial.write(0xEF); delay(5);
  mySerial.write(0x89); delay(5);
  mySerial.write(0xAB); delay(5);
}

void RLS_save_conf(){
  RLS_unlock();
  mySerial.write(0x63); delay(5);    // save configuration parameters = 'c'
  //Serial.println("--> Encoders Configurations saved.\nYou have to reset the Encoder.");
}


float RLS_get_pos(){
  byte b1 = mySerial.read();
  byte b2 = mySerial.read();
  byte b3 = mySerial.read();
  uint32_t pos = b3 + (b2<<8) + (b1<<16);

  pos = (pos>>6);
  float pos_ang = pos*360.0/PPR18;
  return pos_ang;
}
