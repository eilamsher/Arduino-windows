#include <i2c_t3.h>
//#include <Wire.h>

byte b[6], b_old[6];
bool read_done = 0, a = 1;
uint8_t slave_1 = 100;

void requestEvent() {
  //  a = !a;
  if (read_done)
    for (int i = 0; i < 6; i++)
      Wire.write(b[i]);
  else
    for (int i = 0; i < 6; i++)
      Wire.write(b_old[i]);

}

void setup() {
  Wire.begin(I2C_SLAVE, slave_1, I2C_PINS_18_19, I2C_PULLUP_EXT, 400000);
  delay(10);
  Wire.onRequest(requestEvent);
  
  //Wire.begin(4);
  //Wire.onRequest(requestEvent);
  Serial2.begin(115200);
  Serial1.begin(115200);
  pinMode(13, OUTPUT);
}

void loop() {
//  digitalWrite(13, a);
  for (int i = 0; i < 6; i++)
    b_old[i] = b[i];

  read_done = 0;
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
  read_done = 1;
}
