#include <i2c_t3.h>
#define PPR17 131072.0


union u_tag {
  byte b[8];
  float fval[2];
} u;

byte b1[6], b2[6], b3[6];
float first_joint[2];
void setup()
{
  // Setup for Master mode, pins 18/19, external pullups, 400kHz, 200ms default timeout
  Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, 400000);
  Wire.setDefaultTimeout(200000); // 200ms

  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);
}

void loop()
{
  uint8_t target = 0x66; // target Slave address

  digitalWrite(LED_BUILTIN, HIGH);  // LED on

  // Print message
  Serial.print("Reading from Slave: ");

  // Read from Slave
  Wire.requestFrom(target, 8); // Read from Slave (string len unknown, request full buffer)

  // Check if error occured
  if (Wire.getError())
    Serial.print("FAIL\n");
  else
  {
    // If no error then read Rx data into buffer and print

    Wire.read(u.b, Wire.available());

/*
    long pos = b1[0];
    pos = (pos << 8);
    pos = pos | b1[1];
    pos = (pos << 8);
    pos = pos | b1[2];
    pos = (pos >> 7);
    float pos_ang = pos * 360.0 / PPR17;
*/
    Serial.println(" OK\n");
    Serial.println(u.fval[0], 2);
    Serial.println(u.fval[1], 2);
  }

  digitalWrite(LED_BUILTIN, LOW);   // LED off
  delay(100);                       // Delay to space out tests

}
