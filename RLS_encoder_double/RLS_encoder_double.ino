#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
#define PPR17 131072.0

union u_tag {
  float f_val;
  byte bytes[4];
} u;

int a = 0, led = 13, interval = 200;
byte b[9];
//RLS_Encoder_Tiny enc;
float enc_val_x, enc_val_y, enc_val_x2;

// the setup routine runs once when you press reset:
void setup() {
  /*
    Wire.begin();
    lcd.init();                      // initialize the lcd
    lcd.init();  // Print a message to the LCD.
    lcd.backlight();
  */
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);

  Serial2.begin(115200);
  Serial1.begin(115200);

  u.f_val = 543.21;

  delay(5);

  //  Wire.begin(8);                // join i2c bus with address #8
  //  Wire.onRequest(requestEvent); // register event
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
    enc_val_x = parse_bytes(0) + 7.1;
    if (enc_val_x > 180)
      enc_val_x -= 360;



    Serial1.flush();
    while (Serial1.available()) {
      b[3] = Serial1.read();
      b[4] = Serial1.read();
      b[5] = Serial1.read();
      break;
    }
    enc_val_y = parse_bytes(1) + 67;
    if (enc_val_y > 180)
      enc_val_y -= 360;
    Serial.print("x - ");
    Serial.print(enc_val_x, 2);
    Serial.print(":::y - ");
    Serial.println(enc_val_y, 2);

  /*
  Wire.requestFrom(8, 3);    
  b[6] = Wire.read();
  b[7] = Wire.read();
  b[8] = Wire.read();

  //  if (Wire.available())
  //for (int i = 0; i < 4; i++)
  //  u.bytes[i] = Wire.read();

  enc_val_x2 = parse_bytes(2) + 7.1;
  if (enc_val_x2 > 180)
    enc_val_x2 -= 360;



  Serial.print(":::i2c - ");
  Serial.println(enc_val_x2, 2);
  */
  /*
    lcd.setCursor(1, 0);
    lcd.print("x");
    lcd.print(enc_val_x, 2);
    lcd.setCursor(1, 1);
    lcd.print("y");
    lcd.print(enc_val_y, 2);
  */
  delay(10);
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
