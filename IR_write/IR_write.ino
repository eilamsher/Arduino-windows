#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

int RECV_PIN = 11;
// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int ledState = 0;

IRsend irsend(3);

decode_results results;

void setup()
{
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);


  if (buttonState == HIGH) {
    irsend.sendRaw(0x71DB6E89, 20, 38);
    digitalWrite(LED_BUILTIN, HIGH);
  else {
  digitalWrite(LED_BUILTIN, LOW);
  }
  }
}

}
