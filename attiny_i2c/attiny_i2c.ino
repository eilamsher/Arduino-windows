#include <TinyWireS.h>      // wrapper class for I2C slave routines
#define I2C_SLAVE_ADDR  8            // i2c slave address 

void setup(){
  TinyWireS.begin(I2C_SLAVE_ADDR);      // init I2C Slave mode
}

void loop(){
  //byte byteRcvd = 0;
  if (TinyWireS.available()){           // got I2C input!
   
    TinyWireS.send(digitalRead(3));           // send 5 back to master

  }
}
