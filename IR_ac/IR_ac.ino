#include "IRremote.h"
#include "IRelectra.h"
  
void loop()
{
  IRsend irsend(D3);
  IRelectra e(&irsend);
  e.SendElectra(POWER_OFF, MODE_COOL, FAN_LOW, 24, SWING_ON, SLEEP_OFF);
}
