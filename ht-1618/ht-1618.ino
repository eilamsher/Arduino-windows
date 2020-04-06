/* Shift Out Data
 * --------------
 * 
 * Shows a byte, stored in "dato" on a set of 8 LEDs
 *
 * (copyleft) 2005 K3, Malmo University
 * @author: David Cuartielles, Marcus Hannerstig
 * @hardware: David Cuartielles, Marcos Yarza
 * @project: made for SMEE - Experiential Vehicles
 */


int data = 9;
int strob = 8;
int clock = 10;
int oe = 11;
int count = 0;
int dato = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(data, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(strob, OUTPUT);
  pinMode(oe, OUTPUT);
}

void PulseClock(void) {
    digitalWrite(clock, LOW);
    delayMicroseconds(20);
    digitalWrite(clock, HIGH);
    delayMicroseconds(50);
    digitalWrite(clock, LOW);
}

void loop()
{
   dato = 5;
   for (count = 0; count < 8; count++) {
    digitalWrite(data, dato & 01);
    //serialWrite((dato & 01) + 48);
    dato>>=1;
    if (count == 7){
    digitalWrite(oe, LOW);
    digitalWrite(strob, HIGH);

    }
    PulseClock();
     digitalWrite(oe, HIGH);
 }

  delayMicroseconds(20);
  digitalWrite(strob, LOW);
  delay(100);


  //Serial.Write(10);
  //Serial.Write(13);
 delay(100);                  // waits for a moment
}

