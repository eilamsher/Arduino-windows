#include <TM1628.h>
#include <TM16XXFonts.h>






TM1628 disp(9, 7, 8);

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  disp.begin(1,0);  // start with lowest intensity,
  disp.setTime(2,23,10);
}

void loop() {
  // put your main code here, to run repeatedly:

}
