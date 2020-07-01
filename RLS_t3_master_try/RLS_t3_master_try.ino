#include <i2c_t3.h>
#define PPR17 131072.0

union u_tag {
  byte b[8];
  float fval[2];
} u;

//------------Variables---------------
byte b[6];
float enc_val[6];
long pos;
uint8_t slave_add[2] = {0x66, 0x69}; // target Slave addresses

//------------Setup---------------
void setup()
{
  // Setup for Master mode, pins 18/19, external pullups, 400kHz, 200ms default timeout
  Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, 400000);
  Wire.setDefaultTimeout(200000); // 200ms

  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);
  delay(1000);
}


//------------Loop---------------
void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);  // LED on

  // Print message
  Serial.print("Reading from Slave: ");


  Wire.requestFrom(0x66, 6); // Read from Slave (string len unknown, request full buffer)

  // Check if error occured
  if (Wire.getError())
    Serial.println("FAIL\n");
  else
  {
    // If no error then read Rx data into buffer and print

    Wire.read(ub, Wire.available());
    Serial.println(" OK\n");

  }
  for (int i = 0; i < 6; i++) {
    Serial.print(b[i],HEX);
    Serial.print(",");

  }
/*
  Serial.println(u.fval[0], 2);
  Serial.println(u.fval[1], 2);
*/
  digitalWrite(LED_BUILTIN, LOW);   // LED off
  delay(100);                       // Delay to space out tests

}
