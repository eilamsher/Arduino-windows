#include <Wire.h>

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
}


void loop() {
  /*
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write(40);        // sends five bytes
    Wire.write(1);              // sends one byte
    Wire.endTransmission();    // stop transmitting
    delay(2000);
  */
  Wire.beginTransmission(2); // transmit to device #8
  Wire.write(40);        // sends five bytes
  Wire.write(-1);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  delay(2000);

  Wire.beginTransmission(2); // transmit to device #8
  Wire.write(0);        // sends five bytes
  Wire.write(0);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  delay(2000);


  Wire.beginTransmission(4); // transmit to device #8
  Wire.write(40);        // sends five bytes+
  Wire.write(-1);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  delay(2000);

  Wire.beginTransmission(4); // transmit to device #8
  Wire.write(0);        // sends five bytes
  Wire.write(0);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  delay(2000);


  Wire.beginTransmission(6); // transmit to device #8
  Wire.write(40);        // sends five bytes
  Wire.write(-1);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  delay(2000);

  Wire.beginTransmission(6); // transmit to device #8
  Wire.write(0);        // sends five bytes
  Wire.write(0);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  delay(2000);

}
