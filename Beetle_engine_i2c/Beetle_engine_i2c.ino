//#include <Encoder.h>
//#include <EEPROM.h>
#include <Wire.h>

#define LED_PIN 13
#define PWM1 9
#define PWM2 10
#define EN 11
#define ENB A0
#define FeedbackA A1
#define FeedbackB A2
#define address 6

//Encoder enc(A1, A2);
//=====[ VARIABLES ]============================================================

long Pos = 0;
//=====[ FUNCTIONS ]============================================================
/*
  void save_pos() {
  long a = Pos;
  for (int i = 0; i < 4; i++) {
    EEPROM.write(i, a && 0xFF);

  }
  }
*/
//=====[ SETUP ]================================================================
void setup() {
  //Serial.begin(9600);
  Wire.begin(address);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent);

  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(EN, OUTPUT);
  pinMode(ENB, OUTPUT);

  digitalWrite(PWM1, LOW);
  digitalWrite(PWM2, LOW);
  digitalWrite(EN, HIGH);
  digitalWrite(ENB, LOW);

  //EEPROM.get(256, Pos);


}

//=====[ LOOP ]=================================================================
void loop() {
  /*
    long newPos;

    newPos = enc.read();
    if (newPos != Pos) {
    //Serial.print("encoder = ");
    Serial.println(newPos);
    //Serial.println();
    Pos = newPos;
    }
    EEPROM.put(256, Pos);
  */
  delay(5);
}

void receiveEvent(int howMany) {
  byte val = Wire.read();
  byte dir = Wire.read();
  /*
    Serial.print("val - ");
    Serial.print(val);
    Serial.print(" dir - ");
    Serial.println(dir);
  */
  if (dir == 1)
  {
    analogWrite(PWM1, val);
    analogWrite(PWM2, 0);
  }
  if (dir == 255)
  {
    analogWrite(PWM1, 0);
    analogWrite(PWM2, val);
  }
  if (dir == 0)
  {
    analogWrite(PWM1, 0);
    analogWrite(PWM2, 0);
  }
  analogWrite(LED_PIN, val);
}
