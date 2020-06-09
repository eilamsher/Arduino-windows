#include "HX711.h"1

HX711 scale[9];

byte DOUT[9] = {22, 20, 18, 16, 15, 8, 6, 4, 0};
byte CLK[9] = {23, 21, 19, 17, 14, 9, 7, 5, 3};
float b[9] = {453.9559666,-114.2034549,1970.588235,1177.730193,343.0962343,-2466.804979,254.7770701,-2271.352313,-417.6563737};
float a[9] = {0.010053282,0.009596929,0.009803922,0.010706638,0.010460251,0.010373444,0.010615711,0.008896797,0.00989707};
float scale_val[9];

long scale_read[9];

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 9; i++)
    scale[i].begin(DOUT[i], CLK[i]);
}

void loop() {
  for (int i = 0; i < 9; i++){
    scale_read[i] = scale[i].read();
    scale_val[i] = a[i] * scale_read[i] + b[i];
  }

  for (int i = 0; i < 9; i++)
    Serial.println(scale_val[i]);

  Serial.println("");
  //delay(10);
}
