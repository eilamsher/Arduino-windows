// Written by Nick Gammon
// February 2012

#include <Wire.h>

const byte MY_ADDRESS = 42;
const byte OTHER_ADDRESS = 25;

void setup ()
{
  Wire.begin (MY_ADDRESS);
  Wire.onReceive (receiveEvent);
  Wire.onRequest(requestEvent); // register event
  Serial.begin(9600);

}  // end of setup

void loop()
{


  delay(100);
}

// called by interrupt service routine when incoming data arrives
void receiveEvent (int howMany)
{
  int c = Wire.read ();
  Serial.println(c);

  /*
    for (int i = 0; i < howMany; i++)
    {
    byte c = Wire.read ();

    }  // end of for loop*/
}  // end of receiveEvent


void requestEvent() {

  byte a=random(1, 6);
  Wire.write(a); // respond with message of 6 bytes
  // as expected by master
}
