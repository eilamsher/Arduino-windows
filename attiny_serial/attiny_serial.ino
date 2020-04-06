#include <SoftwareSerial.h>
// ***
// *** Define the RX and TX pins. Choose any two
// *** pins that are unused. Try to avoid D0 (pin 5)
// *** and D2 (pin 7) if you plan to use I2C.
// ***
#define RX    3   // *** D3, Pin 2
#define TX    4   // *** D4, Pin 3

// ***
// *** Define the software based mySerial port. Using the
// *** name mySerial so that code can be used on other
// *** platforms that support hardware based mySerial. On
// *** chips that support the hardware mySerial, just
// *** comment this line.
// ***
SoftwareSerial mySerial(RX, TX);
int a = 0;
int check = 0;
void setup() {
  // put your setup code here, to run once:
  // ***
  // *** Initialize the mymySerial port
  // ***
  mySerial.begin(9600);
  mySerial.println("Initializing...");
  pinMode(0,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  mySerial.println(a);
  a++;
  digitalWrite(0,check);
  check=!check;
  delay(1000);
}
