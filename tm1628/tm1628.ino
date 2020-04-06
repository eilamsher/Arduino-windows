#include <TM1628.h>
#include <TM16XXFonts.h>






TM1628 disp(9, 7, 8);

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  disp.begin(1,0);  // start with lowest intensity,
  delay(1000);
  digitalWrite(13, LOW);

  for (int i = 7; i > 0; i--) {
    disp.setSeg(16, i);
    disp.update();
    delay(150);
  }

  delay(300);

  for (int i = 7; i > 0; i--) {
    disp.setCursor(i);
      disp.clear();
    disp.update();
    delay(150);
  }
}

void loop() {
  byte rcv = disp.getButtons();

  digitalWrite(13, rcv > 0 ? HIGH : LOW);
  disp.clear();
  disp.putNumberAt(rcv, 1, false, 10);
//  disp.writeBuffer(); // command 3
  delay(100);
}
