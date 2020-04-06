#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

#include <IRelectra.h>


void setup()   {

}
 
  
void loop()
{
  IRsend irsend(D3);
  IRelectra e(&irsend);
  e.SendElectra(POWER_OFF, MODE_COOL, FAN_LOW, 24, SWING_ON, SLEEP_OFF);
}
