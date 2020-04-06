/* 4-Way Button:  Click, Double-Click, Press+Hold, and Press+Long-Hold Test Sketch

  By Jeff Saltzman
  Oct. 13, 2009

  To keep a physical interface as simple as possible, this sketch demonstrates generating four output events from a single push-button.
  1) Click:  rapid press and release
  2) Double-Click:  two clicks in quick succession
  3) Press and Hold:  holding the button down
  4) Long Press and Hold:  holding the button for a long time
*/

#define buttonPin 3       // analog input pin to use as a digital input
#define IRledPin 0


//=================================================

void setup() {
  // Set button input pin
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH );
  pinMode(IRledPin, OUTPUT);
}

void loop() {
  // Get button event and act accordingly
  int b = checkButton();
  if (b == 1) clickEvent();
  if (b == 2) doubleClickEvent();
  if (b == 3) holdEvent();
  if (b == 4) longHoldEvent();
}

//=================================================
// Events to trigger

void clickEvent() {
  SendChannelPower();

}
void doubleClickEvent() {
  SendVolUp();

}
void holdEvent() {
  SendVolDown();
}
void longHoldEvent() {
  SendInput();
}


//=================================================
//  MULTI-CLICK:  One Button, Multiple Events

// Button timing variables
int debounce = 20;          // ms debounce period to prevent flickering when pressing or releasing the button
int DCgap = 250;            // max ms between clicks for a double click event
int holdTime = 1000;        // ms hold period: how long to wait for press+hold event
int longHoldTime = 3000;    // ms long hold period: how long to wait for press+hold event

// Button variables
boolean buttonVal = HIGH;   // value read from button
boolean buttonLast = HIGH;  // buffered value of the button's previous state
boolean DCwaiting = false;  // whether we're waiting for a double click (down)
boolean DConUp = false;     // whether to register a double click on next release, or whether to wait and click
boolean singleOK = true;    // whether it's OK to do a single click
long downTime = -1;         // time the button was pressed down
long upTime = -1;           // time the button was released
boolean ignoreUp = false;   // whether to ignore the button release because the click+hold was triggered
boolean waitForUp = false;        // when held, whether to wait for the up event
boolean holdEventPast = false;    // whether or not the hold event happened already
boolean longHoldEventPast = false;// whether or not the long hold event happened already

int checkButton() {
  int event = 0;
  buttonVal = digitalRead(buttonPin);
  // Button pressed down
  if (buttonVal == LOW && buttonLast == HIGH && (millis() - upTime) > debounce)
  {
    downTime = millis();
    ignoreUp = false;
    waitForUp = false;
    singleOK = true;
    holdEventPast = false;
    longHoldEventPast = false;
    if ((millis() - upTime) < DCgap && DConUp == false && DCwaiting == true)  DConUp = true;
    else  DConUp = false;
    DCwaiting = false;
  }
  // Button released
  else if (buttonVal == HIGH && buttonLast == LOW && (millis() - downTime) > debounce)
  {
    if (not ignoreUp)
    {
      upTime = millis();
      if (DConUp == false) DCwaiting = true;
      else
      {
        event = 2;
        DConUp = false;
        DCwaiting = false;
        singleOK = false;
      }
    }
  }
  // Test for normal click event: DCgap expired
  if ( buttonVal == HIGH && (millis() - upTime) >= DCgap && DCwaiting == true && DConUp == false && singleOK == true && event != 2)
  {
    event = 1;
    DCwaiting = false;
  }
  // Test for hold
  if (buttonVal == LOW && (millis() - downTime) >= holdTime) {
    // Trigger "normal" hold
    if (not holdEventPast)
    {
      event = 3;
      waitForUp = true;
      ignoreUp = true;
      DConUp = false;
      DCwaiting = false;
      //downTime = millis();
      holdEventPast = true;
    }
    // Trigger "long" hold
    if ((millis() - downTime) >= longHoldTime)
    {
      if (not longHoldEventPast)
      {
        event = 4;
        longHoldEventPast = true;
      }
    }
  }
  buttonLast = buttonVal;
  return event;
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


void SendVolDown() {
  delayMicroseconds(1860);
  pulseIR(500);
  delayMicroseconds(1640);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(460);
  delayMicroseconds(640);
  pulseIR(460);
  delayMicroseconds(620);
  pulseIR(440);
  delayMicroseconds(640);
  pulseIR(440);
  delayMicroseconds(1720);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(480);
  delayMicroseconds(1680);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(480);
  delayMicroseconds(1680);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(600);
  pulseIR(500);
  delayMicroseconds(1660);
  pulseIR(500);
  delayMicroseconds(560);
  pulseIR(520);
  delayMicroseconds(46860);
  pulseIR(500);
  delayMicroseconds(1660);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(460);
  delayMicroseconds(620);
  pulseIR(460);
  delayMicroseconds(600);
  pulseIR(480);
  delayMicroseconds(620);
  pulseIR(460);
  delayMicroseconds(620);
  pulseIR(460);
  delayMicroseconds(1700);
  pulseIR(440);
  delayMicroseconds(640);
  pulseIR(440);
  delayMicroseconds(1720);
  pulseIR(440);
  delayMicroseconds(640);
  pulseIR(440);
  delayMicroseconds(1720);
  pulseIR(440);
  delayMicroseconds(1720);
  pulseIR(440);
  delayMicroseconds(1740);
  pulseIR(420);
  delayMicroseconds(660);
  pulseIR(420);
  delayMicroseconds(1740);
  pulseIR(420);
  delayMicroseconds(44760);
  pulseIR(420);
  delayMicroseconds(1740);
  pulseIR(420);
  delayMicroseconds(660);
  pulseIR(420);
  delayMicroseconds(660);
  pulseIR(420);
  delayMicroseconds(660);
  pulseIR(400);
  delayMicroseconds(700);
  pulseIR(380);
  delayMicroseconds(1780);
  pulseIR(380);
  delayMicroseconds(700);
  pulseIR(380);
  delayMicroseconds(1780);
  pulseIR(360);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(1800);
  pulseIR(360);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(1800);
  pulseIR(360);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(47000);
  pulseIR(400);
  delayMicroseconds(1760);
  pulseIR(380);
  delayMicroseconds(700);
  pulseIR(380);
  delayMicroseconds(700);
  pulseIR(380);
  delayMicroseconds(700);
  pulseIR(360);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(720);
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
  delayMicroseconds(44840);
  pulseIR(360);
  delayMicroseconds(1800);
  pulseIR(340);
  delayMicroseconds(740);
  pulseIR(340);
  delayMicroseconds(740);
  pulseIR(340);
  delayMicroseconds(740);
  pulseIR(340);
  delayMicroseconds(740);
  pulseIR(340);
  delayMicroseconds(1820);
  pulseIR(340);
  delayMicroseconds(740);
  pulseIR(340);
  delayMicroseconds(1820);
  pulseIR(340);
  delayMicroseconds(740);
  pulseIR(340);
  delayMicroseconds(1820);
  pulseIR(340);
  delayMicroseconds(740);
  pulseIR(340);
  delayMicroseconds(740);
  pulseIR(320);
  delayMicroseconds(760);
  pulseIR(340);
  delayMicroseconds(1820);
  pulseIR(320);
  delayMicroseconds(760);
  pulseIR(320);
  delayMicroseconds(47040);
  pulseIR(360);
  delayMicroseconds(1800);
  pulseIR(360);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(720);
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
  delayMicroseconds(1820);
  pulseIR(340);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(1800);
  pulseIR(360);
}


void SendInput() {
  delayMicroseconds(46264);
  pulseIR(540);
  delayMicroseconds(1600);
  pulseIR(520);
  delayMicroseconds(580);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(440);
  delayMicroseconds(660);
  pulseIR(420);
  delayMicroseconds(1720);
  pulseIR(440);
  delayMicroseconds(1720);
  pulseIR(440);
  delayMicroseconds(640);
  pulseIR(440);
  delayMicroseconds(640);
  pulseIR(460);
  delayMicroseconds(1720);
  pulseIR(480);
  delayMicroseconds(580);
  pulseIR(520);
  delayMicroseconds(560);
  pulseIR(520);
  delayMicroseconds(580);
  pulseIR(520);
  delayMicroseconds(1640);
  pulseIR(520);
  delayMicroseconds(560);
  pulseIR(520);
  delayMicroseconds(46840);
  pulseIR(480);
  delayMicroseconds(1680);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(460);
  delayMicroseconds(620);
  pulseIR(460);
  delayMicroseconds(620);
  pulseIR(440);
  delayMicroseconds(1720);
  pulseIR(440);
  delayMicroseconds(1720);
  pulseIR(440);
  delayMicroseconds(640);
  pulseIR(440);
  delayMicroseconds(1720);
  pulseIR(440);
  delayMicroseconds(1740);
  pulseIR(420);
  delayMicroseconds(1740);
  pulseIR(420);
  delayMicroseconds(660);
  pulseIR(420);
  delayMicroseconds(1740);
  pulseIR(420);
  delayMicroseconds(44720);
  pulseIR(400);
  delayMicroseconds(1760);
  pulseIR(400);
  delayMicroseconds(680);
  pulseIR(400);
  delayMicroseconds(680);
  pulseIR(380);
  delayMicroseconds(700);
  pulseIR(380);
  delayMicroseconds(700);
  pulseIR(380);
  delayMicroseconds(1780);
  pulseIR(380);
  delayMicroseconds(1780);
  pulseIR(380);
  delayMicroseconds(700);
  pulseIR(360);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(1800);
  pulseIR(360);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(1800);
  pulseIR(360);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(47000);
  pulseIR(400);
  delayMicroseconds(1760);
  pulseIR(380);
  delayMicroseconds(700);
  pulseIR(380);
  delayMicroseconds(700);
  pulseIR(380);
  delayMicroseconds(700);
  pulseIR(360);
  delayMicroseconds(720);
  pulseIR(380);
  delayMicroseconds(700);
  pulseIR(380);
  delayMicroseconds(700);
  pulseIR(380);
  delayMicroseconds(1780);
  pulseIR(380);
  delayMicroseconds(1780);
  pulseIR(360);
  delayMicroseconds(720);
  pulseIR(360);
  delayMicroseconds(1800);
  pulseIR(360);
  delayMicroseconds(1800);
  pulseIR(360);
  delayMicroseconds(1820);
  pulseIR(340);
  delayMicroseconds(740);
  pulseIR(340);
  delayMicroseconds(1820);
  pulseIR(340);

}
