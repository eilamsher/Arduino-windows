/*
* Arduino LCD Tutorial
*
* Crated by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(1, 2, 4, 5, 6, 7); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 


String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

void setup() { 
    // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
 lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display } 
}
void loop() { 

 /*if (stringComplete) {
  lcd.print(inputString); // Prints "Arduino" on the LCD 

    // clear the string:
    inputString = "";
    stringComplete = false;
  }*/
 /*lcd.print("Arduino"); // Prints "Arduino" on the LCD 
 delay(3000); // 3 seconds delay 
  lcd.setCursor(1,1); // Sets the location at which subsequent text written to the LCD will be displayed 
 lcd.print("Yo yo yo"); // Prints "Arduino" on the LCD 
 lcd.setCursor(2,1); // Sets the location at which subsequent text written to the LCD will be displayed 
 lcd.print("LCD Tutorial"); 
 delay(3000); 
 lcd.clear(); // Clears the display 
 lcd.blink(); //Displays the blinking LCD cursor 
 delay(4000); 
 lcd.setCursor(7,1); 
 delay(3000); 
 lcd.noBlink(); // Turns off the blinking LCD cursor 
 lcd.cursor(); // Displays an underscore (line) at the position to which the next character will be written 
 delay(4000); 
 lcd.noCursor(); // Hides the LCD cursor 
 lcd.clear(); // Clears the LCD screen */
}


void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
      lcd.print(inChar); // Prints "Arduino" on the LCD 
delay(3000);
 lcd.clear(); // Clears the LCD screen */

    /*inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }*/
  }
}
