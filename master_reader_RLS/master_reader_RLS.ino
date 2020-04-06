#include <Wire.h>
float val;
int led = LED_BUILTIN;
byte c1, c2, c3, c4;

void setup()
{
  pinMode(led, OUTPUT);
  Wire.begin();             // join i2c bus (address optional for master)
  Serial.begin(9600);       // start serial for output
}

void loop()
{
  Serial.print("read: ");

  Wire.requestFrom(44, 2);
  
  c1 = Wire.read();   // receive a byte as character
  Serial.print(c1);        // print the character
  Serial.print(".");        // print the character
  c2 = Wire.read();   // receive a byte as character
  Serial.print(c2);        // print the character
  Serial.print("---");        // print the character

  val = c2;
  val = val / 100;
  val = val + c1;
  Serial.println(val);
  delay(500);
}
