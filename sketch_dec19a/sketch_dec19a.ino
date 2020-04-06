#include "Vault.h"


const byte color_range[7][3] = {{0, 0, 0}, {255, 0, 0}, {0, 255, 255}, {255, 255, 0}, {0, 255, 0}, {0, 0, 255}, {255, 0, 255}};
const byte color[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
//const byte color[4] = {1, 2, 3, 4};

Vault va;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  va.blink(5);
}

void loop() {
  // put your main code here, to run repeatedly:
  //va.blink()
  //print_arr_byte(*color_range,7,3);
  va.print_arr_byte(color, 3, 4);
  //va.print_try(color[0]);

  delay(3000);

}
