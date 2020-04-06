//=====[ INCULDE ]==============================================================
#include "RLS_Encoder.h"
#include <Wire.h>

//=====[ Constants ]========================================
#define address 46

//=====[ VARIABLES ]============================================================
RLS_Encoder enc;
float enc1_val;
unsigned int val;
byte a, b;



//=====[ SETUP ]================================================================


void setup() {
  Wire.begin(address);
  Wire.onRequest(requestEvent); // register event
  //Serial.begin(115200); while (!Serial);
  enc.begin(115200);
  delay(5);
}

//=====[ LOOP ]=================================================================
void loop() {

  Serial2.flush();
  //while (Serial2.available()) {
  enc1_val = enc.get_pos();
  //break;
  //}
  enc1_val = enc1_val - 360 - 90;
  if (enc1_val < -180.0)
    enc1_val += 360.0;

  //Serial.print("val : ");
  //Serial.println(enc1_val, 2);
  val = 100 * abs(enc1_val);
  a = val / 100;
  b = val % 100;


  delay(5);
}
//==============================================================================

void requestEvent()
{
  Wire.write(a);     // respond with message of 1 bytes
  Wire.write(b);     // respond with message of 1 bytes
  /*
  Serial.print(a);
  Serial.print(".");
  Serial.println(b);
*/
}
