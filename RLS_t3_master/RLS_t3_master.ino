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
  enc_val[0] = pos * 360.0 / PPR17;

  pos = b[3];
  pos = (pos << 8);
  pos = pos | b[4];
  pos = (pos << 8);
  pos = pos | b[5];
  pos = (pos >> 7);
  enc_val[1] = pos * 360.0 / PPR17;



  digitalWrite(LED_BUILTIN, HIGH);  // LED on

  // Print message
  Serial.print("Reading from Slave: ");

  for (int i = 0; i < 2; i++) {
    // Read from Slave
    Wire.requestFrom(slave_add[i], 8); // Read from Slave (string len unknown, request full buffer)

    // Check if error occured
    if (Wire.getError())
      Serial.println("FAIL\n");
    else
    {
      // If no error then read Rx data into buffer and print

      Wire.read(u.b, Wire.available());
      enc_val[2 * i + 2] = u.fval[0];
      enc_val[2 * i + 3] = u.fval[1];
      Serial.println(" OK\n");

    }
  }
  for (int i = 0; i < 6; i++)
    Serial.println(enc_val[i], 2);


  digitalWrite(LED_BUILTIN, LOW);   // LED off
  delay(100);                       // Delay to space out tests

}
