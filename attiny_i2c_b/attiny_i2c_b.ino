#include "TinyWireS.h"                  // wrapper class for I2C slave routines
#define address  0x8            // i2c slave address (38)

//double b = 5428247.561843584;
long b = 0x1FFFF;
byte data[8];
void setup()
{
  TinyWireS.begin(address);      // init I2C Slave mode
  TinyWireS.onRequest(requestEvent);
  
  for (int i = 0; i < 8; i++) {
    data[i] = (b & 0xFF);
    b = (b >> 8);
  }
}

void loop()
{

}

void requestEvent()
{
  TinyWireS.send(5);
  /*
  for (int i = 7; i >= 0; i--) {
    TinyWireS.send(data[i]);
  }
  */
}
