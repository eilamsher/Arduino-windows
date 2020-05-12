#include <Encoder.h>
IntervalTimer myTimer;

// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder enc(0, 1);
//   avoid using pins with LEDs attached

elapsedMicros a;

long pos  = 0;
long last_pos = 0;
long t;
float interv;
float ang_speed;
void setup() {
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  analogWrite(9,20);
  analogWrite(10,0);
}

void loop() {
  interv = a-t;
  t = a;
  last_pos = pos;
  pos = enc.read();
  ang_speed = (pos-last_pos)/interv;
  Serial.println(last_pos-pos);
  /*
  Serial.print("---");
  Serial.print(interv);
  Serial.print("---");
  Serial.println(ang_speed);
  */
  delay(20);
}
