#include <Wire.h>
#define PPR17 131072.0

int a = 0;
byte b[12];
//RLS_Encoder_Tiny enc;
float enc_val[4], err[4] = { -123, 33.9, 71.5, -99.7}; //{235.9, 36.6, 0, 247};

// the setup routine runs once when you press reset:
void setup() {

  Wire.begin();
  Serial2.begin(115200);
  Serial1.begin(115200);
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}

// the loop routine runs over and over again forever:
void loop() {
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

  Wire.requestFrom(8, 6);
  while (Wire.available())
    for (int i = 6; i < 12; i++)
      b[i] = Wire.read();

  for (int i = 0; i < 4; i++) {
    enc_val[i] = parse_bytes(i * 3) + err[i];
    if (enc_val[i] > 180)
      enc_val[i] -= 360;
  }

  for (int i = 0; i < 4; i++) {
    Serial.print(enc_val[i], 2);
    Serial.print(",");
  }
  Serial.println("");
  /*
    for (int i = 6; i < 12; i++) {
    Serial.print(b[i], HEX);
    Serial.print(",");
    }
    Serial.println("");*/
  delay(5);
}

float parse_bytes(byte a) {
  long pos = b[0 + a];
  pos = (pos << 8);
  pos = pos | b[1 + a];
  pos = (pos << 8);
  pos = pos | b[2 + a];
  pos = (pos >> 7);
  float pos_ang = pos * 360.0 / PPR17;
  return pos_ang;
}
