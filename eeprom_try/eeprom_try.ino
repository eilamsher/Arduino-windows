#include <EEPROM.h>

long Pos = 10, outputValue;

void setup() {
  // put your setup code here, to run once:
  EEPROM.get(512, Pos);
  Serial.begin(9600);
  Serial.print(Pos);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(Pos);
  delay(5);
}
