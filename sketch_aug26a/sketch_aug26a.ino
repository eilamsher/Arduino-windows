#include "LedControl.h"

byte button = 2;
byte pinA = 3;  // Connected to CLK on KY-040
byte pinB = 4;  // Connected to DT on KY-040
byte ledA = 5;
byte ledB = 6;
byte ledC = 7;


int encoderPosCount = 0;
int pinALast;
int aVal;
byte range = 15;




/*
  7 digit pinout
  pin 12 is connected to the DataIn
  pin 13 is connected to the CLK
  pin 10 is connected to LOAD
  We have only a single MAX72XX.
*/


LedControl lc = LedControl(12, 13, 10, 1);


void setup() {
  pinMode (pinA, INPUT);
  pinMode (pinB, INPUT);
  pinMode (button, INPUT_PULLUP);
  pinMode (ledA, OUTPUT);
  pinMode (ledB, OUTPUT);
  pinMode (ledC, OUTPUT);


  lc.shutdown(0, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 8);
  /* and clear the display */
  lc.clearDisplay(0);
  /* Read Pin A
    Whatever state it's in will reflect the last position
  */
  pinALast = digitalRead(pinA);
  Serial.begin (9600);


  lc.setChar(0, 0, '8', false);
  lc.setChar(0, 1, '0', false);
  lc.setChar(0, 2, '0', false);
  lc.setChar(0, 3, '8', false);

}

void loop() {
  aVal = digitalRead(pinA);
  if (aVal != pinALast) { // Means the knob is rotating
    // if the knob is rotating, we need to determine direction
    // We do that by reading pin B.
    if (digitalRead(pinB) != aVal) {  // Means pin A Changed first - We're Rotating Clockwise
      encoderPosCount ++;
      if (encoderPosCount > range) encoderPosCount = -range;
    } else {// Otherwise B changed first and we're moving CCW
      encoderPosCount--;
      if (encoderPosCount < -range) encoderPosCount = range;
    }



    Serial.print ("Rotated: ");
    Serial.print("Encoder Position: ");
    Serial.println(encoderPosCount);

  }
  pinALast = aVal;
}
