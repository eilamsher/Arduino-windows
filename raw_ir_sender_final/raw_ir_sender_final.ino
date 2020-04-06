

const int IRledPin =  3;

void setup()   {
  pinMode(IRledPin, OUTPUT);
}

void loop()
{
  SendVolUp();
  //SendChannelPower();
  delay(3000);
}

// This procedure sends a 38KHz pulse to the IRledPin
// for a certain # of microseconds. We'll use this whenever we need to send codes
void pulseIR(long microsecs) {
  // we'll count down from the number of microseconds we are told to wait

  cli();  // this turns off any background interrupts

  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
    digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
    delayMicroseconds(10);         // hang out for 10 microseconds
    digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
    delayMicroseconds(10);         // hang out for 10 microseconds

    // so 26 microseconds altogether
    microsecs -= 26;
  }

  sei();  // this turns them back on
}

void SendChannelPower() {
  delayMicroseconds(13800);
  pulseIR(540);
  delayMicroseconds(1620);
  pulseIR(540);
  delayMicroseconds(540);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(480);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(460);
  delayMicroseconds(1720);
  pulseIR(520);
  delayMicroseconds(1640);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(460);
  delayMicroseconds(1700);
  pulseIR(520);
  delayMicroseconds(560);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(460);
  delayMicroseconds(620);
  pulseIR(460);
  delayMicroseconds(1700);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(460);
  delayMicroseconds(46920);
  pulseIR(480);
  delayMicroseconds(1680);
  pulseIR(460);
  delayMicroseconds(620);
  pulseIR(460);
  delayMicroseconds(620);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(520);
  delayMicroseconds(1660);
  pulseIR(480);
  delayMicroseconds(580);
  pulseIR(520);
  delayMicroseconds(560);
  pulseIR(520);
  delayMicroseconds(1640);
  pulseIR(520);
  delayMicroseconds(560);
  pulseIR(540);
  delayMicroseconds(1640);
  pulseIR(500);
  delayMicroseconds(1660);
  pulseIR(520);
  delayMicroseconds(1640);
  pulseIR(540);
  delayMicroseconds(540);
  pulseIR(540);
  delayMicroseconds(1620);
  pulseIR(500);
  delayMicroseconds(44720);
  pulseIR(500);
  delayMicroseconds(1640);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(480);
  delayMicroseconds(620);
  pulseIR(480);
  delayMicroseconds(580);
  pulseIR(480);
  delayMicroseconds(1680);
  pulseIR(480);
  delayMicroseconds(1700);
  pulseIR(440);
  delayMicroseconds(620);
  pulseIR(460);
  delayMicroseconds(1720);
  pulseIR(440);
  delayMicroseconds(640);
  pulseIR(440);
  delayMicroseconds(640);
  pulseIR(440);
  delayMicroseconds(640);
  pulseIR(440);
  delayMicroseconds(1740);
  pulseIR(420);
  delayMicroseconds(640);
  pulseIR(440);
  delayMicroseconds(46960);
  pulseIR(420);
  delayMicroseconds(1740);
  pulseIR(420);
  delayMicroseconds(660);
  pulseIR(420);
  delayMicroseconds(660);
  pulseIR(400);
  delayMicroseconds(680);
  pulseIR(400);
  delayMicroseconds(680);
  pulseIR(400);
  delayMicroseconds(1760);
  pulseIR(400);
  delayMicroseconds(680);
  pulseIR(380);
  delayMicroseconds(700);
  pulseIR(380);
  delayMicroseconds(1780);
  pulseIR(380);
  delayMicroseconds(700);
  pulseIR(360);
  delayMicroseconds(1800);
  pulseIR(380);
  delayMicroseconds(1780);
  pulseIR(380);
  delayMicroseconds(1800);
  pulseIR(360);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(1800);
  pulseIR(360);
}



void SendVolUp() {
  delayMicroseconds(31508);
  pulseIR(500);
  delayMicroseconds(1660);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(500);
  delayMicroseconds(600);
  pulseIR(460);
  delayMicroseconds(620);
  pulseIR(480);
  delayMicroseconds(1680);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(460);
  delayMicroseconds(1680);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(480);
  delayMicroseconds(620);
  pulseIR(440);
  delayMicroseconds(1720);
  pulseIR(440);
  delayMicroseconds(620);
  pulseIR(460);
  delayMicroseconds(48020);
  pulseIR(440);
  delayMicroseconds(1720);
  pulseIR(440);
  delayMicroseconds(640);
  pulseIR(440);
  delayMicroseconds(640);
  pulseIR(440);
  delayMicroseconds(640);
  pulseIR(440);
  delayMicroseconds(640);
  pulseIR(460);
  delayMicroseconds(1700);
  pulseIR(440);
  delayMicroseconds(1740);
  pulseIR(420);
  delayMicroseconds(660);
  pulseIR(420);
  delayMicroseconds(1740);
  pulseIR(420);
  delayMicroseconds(660);
  pulseIR(420);
  delayMicroseconds(1740);
  pulseIR(400);
  delayMicroseconds(1760);
  pulseIR(400);
  delayMicroseconds(1780);
  pulseIR(380);
  delayMicroseconds(700);
  pulseIR(360);
  delayMicroseconds(1800);
  pulseIR(360);
  delayMicroseconds(43720);
  pulseIR(380);
  delayMicroseconds(1780);
  pulseIR(380);
  delayMicroseconds(700);
  pulseIR(380);
  delayMicroseconds(700);
  pulseIR(360);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(740);
  pulseIR(360);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(700);
  pulseIR(380);
  delayMicroseconds(1800);
  pulseIR(360);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(1800);
  pulseIR(360);
  delayMicroseconds(700);
  pulseIR(360);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(740);
  pulseIR(360);
  delayMicroseconds(1800);
  pulseIR(360);
  delayMicroseconds(700);
  pulseIR(360);
  delayMicroseconds(48120);
  pulseIR(380);
  delayMicroseconds(1780);
  pulseIR(380);
  delayMicroseconds(700);
  pulseIR(380);
  delayMicroseconds(700);
  pulseIR(380);
  delayMicroseconds(700);
  pulseIR(380);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(1800);
  pulseIR(360);
  delayMicroseconds(1800);
  pulseIR(360);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(1800);
  pulseIR(360);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(1800);
  pulseIR(360);
  delayMicroseconds(1800);
  pulseIR(360);
  delayMicroseconds(1800);
  pulseIR(360);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(1800);
  pulseIR(360);
}
