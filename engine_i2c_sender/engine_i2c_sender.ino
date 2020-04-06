#include <Wire.h>


// Rotary Encoder Module connections
const int PinSW = 3; // Rotary Encoder Switch
const int PinDT = 4;  // DATA signal
const int PinCLK = 2;  // CLOCK signal

// Variables to debounce Rotary Encoder
long TimeOfLastDebounce = 0;
int DelayofDebounce = 0.01;

// Store previous Pins state
int PreviousCLK;
int PreviousDATA;

byte displaycounter = 0; // Store current counter value

// Library used for LED MATRIX 8x8

/*  PAROLA_HW,    ///< Use the Parola style hardware modules.
    GENERIC_HW,   ///< Use 'generic' style hardware modules commonly available.
    ICSTATION_HW, ///< Use ICStation style hardware module.
    FC16_HW       ///< Use FC-16 style hardware module.
*/



void setup() {
  // Put current pins state in variables
  Wire.begin(); // join i2c bus (address optional for master)
  PreviousCLK = digitalRead(PinCLK);
  PreviousDATA = digitalRead(PinDT);
  Serial.begin (9600);

  // Set the Switch pin to use Arduino PULLUP resistors
  pinMode(PinSW, INPUT_PULLUP);

  // Start and setup the LED MATRIX at startup

  Serial.println(displaycounter);

}
void loop() {
  // If enough time has passed check the rotary encoder
  if ((millis() - TimeOfLastDebounce) > DelayofDebounce) {

    check_rotary();  // Rotary Encoder check routine below

    PreviousCLK = digitalRead(PinCLK);
    PreviousDATA = digitalRead(PinDT);

    TimeOfLastDebounce = millis(); // Set variable to current millis() timer
  }

  // Check if Rotary Encoder switch was pressed
  if (digitalRead(PinSW) == LOW) {
    //    displaycounter = 0; // Reset counter to zero
    Serial.println("sent");
    Wire.beginTransmission(42); // transmit to device #8
    Wire.write(displaycounter);              // sends one byte
    Wire.endTransmission();    // stop transmitting
    while (digitalRead(PinSW) == LOW);
  }
}


// Check if Rotary Encoder was moved
void check_rotary() {

  if ((PreviousCLK == 0) && (PreviousDATA == 1)) {
    if ((digitalRead(PinCLK) == 1) && (digitalRead(PinDT) == 0)) {
      displaycounter++;
      Serial.println(displaycounter);
    }
    if ((digitalRead(PinCLK) == 1) && (digitalRead(PinDT) == 1)) {
      displaycounter--;
      Serial.println(displaycounter);
    }
  }

  if ((PreviousCLK == 1) && (PreviousDATA == 0)) {
    if ((digitalRead(PinCLK) == 0) && (digitalRead(PinDT) == 1)) {
      displaycounter++;
      Serial.println(displaycounter);
    }
    if ((digitalRead(PinCLK) == 0) && (digitalRead(PinDT) == 0)) {
      displaycounter--;
      Serial.println(displaycounter);
    }
  }

  if ((PreviousCLK == 1) && (PreviousDATA == 1)) {
    if ((digitalRead(PinCLK) == 0) && (digitalRead(PinDT) == 1)) {
      displaycounter++;
      Serial.println(displaycounter);
    }
    if ((digitalRead(PinCLK) == 0) && (digitalRead(PinDT) == 0)) {
      displaycounter--;
      Serial.println(displaycounter);
    }
  }

  if ((PreviousCLK == 0) && (PreviousDATA == 0)) {
    if ((digitalRead(PinCLK) == 1) && (digitalRead(PinDT) == 0)) {
      displaycounter++;
      Serial.println(displaycounter);
    }
    if ((digitalRead(PinCLK) == 1) && (digitalRead(PinDT) == 1)) {
      displaycounter--;
      Serial.println(displaycounter);
    }
  }
}
