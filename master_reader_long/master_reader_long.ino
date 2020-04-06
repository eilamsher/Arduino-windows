// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

#include <Wire.h>
#define PPR17 131072.0
#define buffer_size 11

union u_tag {
  float f_val;
  byte bytes[4];
} u;

float pos_ang, buff[buffer_size], elements[buffer_size], num_of_elements[buffer_size];
byte b1, b2, b3, boo;
long pos, index = 0, element_index;



void data_buffer() {
  //insert new element to buff
  int abc = pos_ang * 100;
  buff[index % buffer_size] = (float)abc / 100;
  index++;

  //initialize
  for (int i = 0; i < buffer_size; i++) {
    elements[i] = -1000000;
    num_of_elements[i] = 0;
  }
  elements[0] = buff[0];
  num_of_elements[0] = 1;
  element_index = 1;

  //counting elements
  for (int i = 1; i < buffer_size; i++) {
    for (int j = 0; j < buffer_size; j++) {
      boo = 0;
      if (buff[i] == elements[j]) {
        num_of_elements[j]++;
        boo = 1;
        break;
      }
    }
    if (!boo) {
      elements[element_index] = buff[i];
      num_of_elements[element_index] = 1;
      element_index++;
    }
  }

  /*
    for (int i = 0; i < buffer_size; i++) {
      if (elements[i] == -1000000)
        break;
      Serial.print(elements[i], 5);
      Serial.print(" - ");
      Serial.print(num_of_elements[i]);
      Serial.println("");
    }
    Serial.println("-----------------");
  */
  abc = num_of_elements[0];
  element_index = 0;
  for (int i = 1; i < buffer_size; i++) {
    if (num_of_elements[i] > abc) {
      abc = num_of_elements[i];
      element_index = i;
    }
  }
  Serial.print(elements[element_index], 5);
  Serial.print(" - ");
  Serial.println(num_of_elements[element_index]);

}




void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {
  Wire.requestFrom(8, 3);    // request 6 bytes from slave device #8

  b1 = Wire.read();
  b2 = Wire.read();
  b3 = Wire.read();
  /*
    Serial.print(b1, HEX);
    Serial.print("-");
    Serial.print(b2, HEX);
    Serial.print("-");
    Serial.print(b3, HEX);
    Serial.print("--------");
  */
  pos = b1;
  pos = (pos << 8);
  pos = pos | b2;
  pos = (pos << 8);
  pos = pos | b3;
  pos = (pos >> 7);
  pos_ang = pos * 360.0 / PPR17;
  Serial.println(pos_ang, 2);

  //data_buffer();

  delay(100);
}



/*
  for (int i = 0; i < 4; i++) {
  u.bytes[i] = Wire.read(); // receive a byte as character
  }
  c = u.f_val;
  Serial.println(c,4);*/
