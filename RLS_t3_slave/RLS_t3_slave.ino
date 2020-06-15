#include <i2c_t3.h>
#define PPR17 131072.0

union u_tag {
  byte b[8];
  float fval[2];
} u;

//------------Functions---------------
void requestEvent(void);

//------------Variables---------------
byte b[6];
float joint;
long pos;

//------------Setup---------------
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT); // LED
  // Setup for Slave mode, address 0x66, pins 18/19, external pullups, 400kHz
  Wire.begin(I2C_SLAVE, 0x66, I2C_PINS_18_19, I2C_PULLUP_EXT, 400000);

  // register events
  Wire.onRequest(requestEvent);

  Serial1.begin(115200);
  Serial2.begin(115200);
}

//------------Loop---------------
void loop()
{
  Serial1.flush();
  while (Serial1.available()) {
    b[0] = Serial1.read();
    b[1] = Serial1.read();
    b[2] = Serial1.read();
    break;
  }
  Serial2.flush();
  while (Serial2.available()) {
    b[3] = Serial2.read();
    b[4] = Serial2.read();
    b[5] = Serial2.read();
    break;
  }

  pos = b[0];
  pos = (pos << 8);
  pos = pos | b[1];
  pos = (pos << 8);
  pos = pos | b[2];
  pos = (pos >> 7);
  joint = pos * 360.0 / PPR17;
  u.fval[0] = joint;



  pos = b[3];
  pos = (pos << 8);
  pos = pos | b[4];
  pos = (pos << 8);
  pos = pos | b[5];
  pos = (pos >> 7);
  u.fval[1] = pos * 360.0 / PPR17;

  delay(1);
}

//
// handle Tx Event (outgoing I2C data)
//
void requestEvent(void)
{
  Wire.write(u.b, 8);
  /*
    for (int i = 0; i < 8; i++)
    Wire.write(b[i]);
  */
}
