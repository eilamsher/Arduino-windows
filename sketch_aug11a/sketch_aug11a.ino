#include "LedControl.h"

int sec = 300;
unsigned long t = 0, last_t = 0;










/*
  Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
  pin 12 is connected to the DataIn
  pin 13 is connected to the CLK
  pin 10 is connected to LOAD
  We have only a single MAX72XX.
*/
LedControl lc = LedControl(12, 13, 10, 1);

/* we always wait a bit between updates of the display */
unsigned long delaytime = 250;

void setup() {
  Serial.begin(9600);

  lc.shutdown(0, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 8);
  /* and clear the display */
  lc.clearDisplay(0);



  lc.setChar(0, 0, '0', false);
  lc.setChar(0, 1, '0', false);
  lc.setChar(0, 2, '5', true);
  lc.setChar(0, 3, '0', false);
}






void writeArduinoOn7Segment() {
  lc.setChar(0, 0, 'a', false);
  delay(delaytime);
  lc.setRow(0, 0, 0x05);
  delay(delaytime);
  lc.setChar(0, 0, 'd', false);
  delay(delaytime);
  lc.setRow(0, 0, 0x1c);
  delay(delaytime);
  lc.setRow(0, 0, B00010000);
  delay(delaytime);
  lc.setRow(0, 0, 0x15);
  delay(delaytime);
  lc.setRow(0, 0, 0x1D);
  delay(delaytime);
  lc.clearDisplay(0);
  delay(delaytime);
}



void scrollDigits() {
  for (int i = 0; i < 13; i++) {
    lc.setDigit(0, 3, i, false);
    lc.setDigit(0, 2, i + 1, false);
    lc.setDigit(0, 1, i + 2, false);
    lc.setDigit(0, 0, i + 3, false);
    delay(delaytime);
  }
  lc.clearDisplay(0);
  delay(delaytime);
}

void loop() {
  //writeArduinoOn7Segment();
  //scrollDigits();
  String str;
  char x, b[2];
  t = millis();

  if (t - last_t >= 1000) {

    last_t = t;
    sec--;
    str = String(sec / 60);
    str.toCharArray(b, 2);
    lc.setChar(0, 2, b[0], true);



    str = String((sec % 60) / 10);
    str.toCharArray(b, 2);
    lc.setChar(0, 1, b[0], false);
    str = String((sec % 60) % 10);
    str.toCharArray(b, 2);
    lc.setChar(0, 0, b[0], false);

  }


}
