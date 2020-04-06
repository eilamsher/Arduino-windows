#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
#define PPR17 131072.0

union u_tag {
  float f_val;
  byte bytes[4];
} u1, u2;

int led = 13;
byte b[6];
float enc_val_x, enc_val_y;

// the setup routine runs once when you press reset:
void setup() {
  Wire.begin(4);
  Wire.onRequest(requestEvent);
  pinMode(led, OUTPUT);
  Serial2.begin(115200);
  Serial1.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() {
  Serial2.flush();
  while (Serial2.available()) {
    b[0] = Serial2.read();
    b[1] = Serial2.read();
    b[2] = Serial2.read();
    break;
  }
  //u1.f_val = parse_bytes(0);

  Serial1.flush();
  while (Serial1.available()) {
    b[3] = Serial1.read();
    b[4] = Serial1.read();
    b[5] = Serial1.read();
    break;
  }
  //u2.f_val = parse_bytes(1);
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

void requestEvent() {
  /*
    for (int i = 0; i < 4; i++) {
      Wire.write(u1.bytes[i]);
    }
    for (int i = 0; i < 4; i++) {
      Wire.write(u2.bytes[i]);
    }
  */
  digitalWrite(led, HIGH);
  for (int i = 0; i < 6; i++) {
    Wire.write(b[i]);
  }
  digitalWrite(led, LOW);
}
