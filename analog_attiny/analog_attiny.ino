// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A2;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 0; // Analog output pin that the LED is attached to

int sensorValue = 5;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
int x=200;
void setup() {
m 
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  //outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:
  //analogWrite(analogOutPin, outputValue);
  x=sensorValue*2+100;
  digitalWrite(0, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(x);                       // wait for a second
  digitalWrite(0, LOW);    // turn the LED off by making the voltage LOW
  delay(x);       
  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
}
