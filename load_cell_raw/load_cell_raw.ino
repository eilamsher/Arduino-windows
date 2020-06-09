#include "HX711.h"

#define DOUT  20
#define CLK  21

HX711 scale;
HX711 scale2;

float calibration_factor = -10000; //-7050 worked for my 440lb max scale setup
long var, var2;

void setup() {
  Serial.begin(9600);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");

  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare(); //Reset the scale to 0

  scale2.begin(22, 23);

  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
}

void loop() {

  var = scale.read_average(30);
  //var2 = scale2.read_average(5);

  Serial.println(var);
  Serial.println(3130 + 0.01*var);
  //delay(10);
}
