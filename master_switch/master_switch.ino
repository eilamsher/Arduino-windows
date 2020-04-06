/* switch
 * 
 * Each time the input pin goes from LOW to HIGH (e.g. because of a push-button
 * press), the output pin is toggled from LOW to HIGH or HIGH to LOW.  There's
 * a minimum delay between toggles to debounce the circuit (i.e. to ignore
 * noise).  
 *
 * David A. Mellis
 * 21 November 2006
 */
#include <Wire.h>

int inPin = 3;         // the number of the input pin
int outPin = 2;       // the number of the output pin

int state = HIGH;      // the current state of the output pin
int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  pinMode(inPin, INPUT);
  pinMode(outPin, OUTPUT);
}

byte x = 0;

void loop()
{
  reading = digitalRead(inPin);

  // if the input just went from LOW and HIGH and we've waited long enough
  // to ignore any noise on the circuit, toggle the output pin and remember
  // the time
  if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    if (state == HIGH){
      state = LOW;
      x=0;
    }
    else{
      state = HIGH;
      x=1;
    }
    time = millis();    
  }

      Wire.beginTransmission(8); // transmit to device #8
      Wire.write(x);              // sends one byte
      Wire.endTransmission();    // stop transmitting

  previous = reading;
}
