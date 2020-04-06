#include <Wire.h>
//#include "RLS_Encoder_Tiny.h"
#define PPR17 131072.0

union u_tag {
  float f_val;
  byte bytes[4];
} u;

int a = 0, led = 13, interval = 200;
byte b1, b2, b3;
//RLS_Encoder_Tiny enc;
float enc_val;

// the setup routine runs once when you press reset:
void setup() {

  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  //Serial.begin(115200);

  Serial2.begin(115200);

  delay(5);
  u.f_val = 543.21;

  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

// the loop routine runs over and over again forever:
void loop() {

  Serial2.flush();
  while (Serial2.available()) {

    b1 = Serial2.read();
    b2 = Serial2.read();
    b3 = Serial2.read();

    //interval = 100;
    break;
  }
  /*
  long pos = b1;
  pos = (pos << 8);
  pos = pos | b2;
  pos = (pos << 8);
  pos = pos | b3;
  pos = (pos >> 7);
  u.f_val = pos * 360.0 / PPR17;
  */
  //Serial.println(u.f_val,2);
  delay(5);
}

void requestEvent() {
  /*
  for (int i = 0; i < 4; i++) {
    Wire.write(u.bytes[i]);
  }
  */
  
    Wire.write(b1);
    Wire.write(b2);
    Wire.write(b3);
  
}
