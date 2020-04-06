#include <Wire.h>

int led = 8, ana = A3, val = 0;
// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event

  pinMode(led, OUTPUT);
  pinMode(ana, INPUT);

}

// the loop routine runs over and over again forever:
void loop() {
  /*
  val = analogRead(ana);
  analogWrite(led, val);   // turn the LED on (HIGH is the voltage level)
  delay(10);
  */
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);
  digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(500);
}

void requestEvent() {
  Wire.write(val); // respond with message of 6 bytes
  // as expected by master
}
