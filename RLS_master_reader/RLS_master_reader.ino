#include <Wire.h>
#define PPR17 131072.0

union u_tag {
  float f_val;
  byte bytes[4];
} u1, u2;
byte b[12];
float enc_val[4], error[] = {7.2, 68.75, 34.8, 238.2}; //{-352.8, -291.25, -325.2, -121.8};
long pos;

void setup()
{
  Wire.begin();
  Serial.begin(115200);
  Serial2.begin(115200);
  Serial1.begin(115200);
}

void loop()
{
  Serial2.flush();
  while (Serial2.available()) {
    b[0] = Serial2.read();
    b[1] = Serial2.read();
    b[2] = Serial2.read();
    break;
  }

  Serial1.flush();
  while (Serial1.available()) {
    b[3] = Serial1.read();
    b[4] = Serial1.read();
    b[5] = Serial1.read();
    break;
  }
  /*
    Wire.requestFrom(2, 8);

    while (Wire.available()) {
      for (int i = 0; i < 4; i++) {
        u1.bytes[i] = Wire.read();
      }
      for (int i = 0; i < 4; i++) {
        u2.bytes[i] = Wire.read();
      }
    }
    Serial.print("x-");
    Serial.print(u1.f_val, 2);
    Serial.print(" y-");
    Serial.println(u2.f_val, 2);
  */
  /*
    Wire.requestFrom(2, 6);

    while (Wire.available()) {
      for (int i = 0; i < 6; i++) {
        b[i] = Wire.read();
      }
    }
  */
  Wire.requestFrom(4, 6);

  while (Wire.available()) {
    for (int i = 6; i < 12; i++) {
      b[i] = Wire.read();
    }
  }

  for (int i = 0; i < 4; i++) {
    pos = b[0 + i * 3];
    pos = (pos << 8);
    pos = pos | b[1 + i * 3];
    pos = (pos << 8);
    pos = pos | b[2 + i * 3];
    pos = (pos >> 7);
    enc_val[i] = pos * 360.0 / PPR17;
    enc_val[i] += error[i];
    if (enc_val[i] > 180)
      enc_val[i] -= 360;
    Serial.print(i);
    Serial.print(" - ");
    Serial.print(enc_val[i], 2);
    Serial.print(":::");
  }
  Serial.println();
  delay(5);
}
