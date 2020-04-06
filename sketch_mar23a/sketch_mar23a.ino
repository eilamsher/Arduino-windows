#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
#define PPR17 131072.0

int led = 8;
byte b[3];
float pos_ang;
long pos;


void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)

  Wire.begin();
  lcd.init();  // Print a message to the LCD.
    digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)


  lcd.backlight();
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.flush();
  while (Serial.available()) {
    b[0] = Serial.read();
    b[1] = Serial.read();
    b[2] = Serial.read();
    break;
  }
  pos = b[0];
  pos = (pos << 8);
  pos = pos | b[1];
  pos = (pos << 8);
  pos = pos | b[2];
  pos = (pos >> 7);
  pos_ang = pos * 360.0 / PPR17;

  lcd.setCursor(1, 0);
  lcd.print(pos_ang, 2);
  
  delay(200);               // wait for a second
}
