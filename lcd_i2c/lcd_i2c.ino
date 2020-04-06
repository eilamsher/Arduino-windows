#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

unsigned long preMillis = 0;
unsigned long preMicro = 0;
int sec = 13;
int micro=6000;
void setup()
{
  lcd.init();                      // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();




}


void loop()
{
  lcd.setCursor(0, 1);
  lcd.print("I am YELLOW");

  if (sec == 0) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("BOOM BOOM BOOM");
    delay(100000000000);
  }


  if (sec > 60) {
    if (millis() - preMillis >= 1000) {
      lcd.setCursor(0, 0);

      preMillis = millis();
      sec--;
      lcd.print(sec / 60);

      lcd.print(":");
      if (sec % 60 < 10)
        lcd.print("0");
      lcd.print(sec % 60);

    }
  }
  else {
    if (millis() - preMillis >= 1000) {
      lcd.setCursor(0, 0);

      preMillis = millis();
      preMicro=preMillis;
      sec--;
      if (sec % 60 < 10)
        lcd.print("0");
      lcd.print(sec % 60);

      lcd.print(":");


    }
    if (millis() - preMicro >= 500) {
       lcd.setCursor(3, 0);


      preMicro = millis();
      micro--;
      lcd.print(micro % 10);


    }
  }
}
