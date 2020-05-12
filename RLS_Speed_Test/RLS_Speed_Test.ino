#include <Wire.h>

#define PPR17 131072.0
IntervalTimer myTimer;



//float a;
elapsedMicros a;
long bbb, bbb1;
byte b[12];
float enc_val[4], error[] = {7.2, 68.75, 34.8, 238.2}; //{-352.8, -291.25, -325.2, -121.8};
long pos;



void setup() {
  // put your setup code here, to run once:
  Wire.begin();

  Serial.begin(115200);
  Serial2.begin(115200);
  Serial1.begin(115200);
  myTimer.begin(blinkLED, 150000);  // blinkLED to run every 0.15 seconds

}

void blinkLED() {
  bbb1 = a - bbb;
  bbb = a;
  Serial.println(bbb1);

}

void loop() {
  // put your main code here, to run repeatedly:

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
    /*
        Serial.print(i);
        Serial.print(" - ");
        Serial.print(enc_val[i], 2);
        Serial.print(":::");
    */
  }



  //Serial.print(b[6],HEX);




  /*
    b=a;
    delay(10);
    b=a-b;
    Serial.println(b);

    delay(100);
  */
}
