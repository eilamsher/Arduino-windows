#include "LedControl.h"
#include <Wire.h>

#define num_of_mod 3

// mod_status - the input from slave to master: 0-not ready, 1-playing, 2-lost, 3-win, 4-sleep, 255-disconnect





int sec = 300;
unsigned long t = 0, last_t = 0;


const byte KEYPAD_ADDRESS = 42;
const byte WIRES_ADDRESS = 44;
const byte MORSE_ADDRESS = 46;
const byte SILENT_ADDRESS = 50;
const byte MOD[] = {44};//, 43, 44};
byte level[] = {1}, mod_status[] = {0, 0, 0};
byte hold_on = 0, let_go = 0; //used to erase sum after a number of seconds
/*
  7 digit pinout
  pin 12 is connected to the DataIn
  pin 13 is connected to the CLK
  pin 11 is connected to LOAD
  We have only a single MAX72XX.
*/


LedControl lc = LedControl(12, 13, 11, 1);

// locker things

byte button = 8;
byte pinA = 10;  // Connected to CLK on KY-040
byte pinB = 9;  // Connected to DT on KY-040
/*byte ledA = 5;
  byte ledB = 6;
  byte ledC = 7;
  byte leds[] = {ledA, ledB, ledC};*/

int encoderPosCount = 0;
int pinALast;
int aVal;
byte range = 15;
byte stage = 0;
int all_input;
byte button_reading = 0;
int sum;



// Variables will change:
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

int graph_pool[3][31] = {
  {1, 27, -15, 6, 19, 7, -12, -6, 2, 15, 14, -4, -13, 28, 29, -1, -24, 9, 2, -7, 13, -28, -3, 3, -22, -14, 30, 18, -17, -27, 23},
  {0, 27, -15, 6, 19, 7, -13, -6, 2, 15, 14, -4, -12, 29, 28, -1, -24, 9, 2, -7, 1, -28, -5, 3, -22, -14, 30, 20, -17, -27, 24},
  { -4, 20, -15, 19, 6, 7, -19, -6, 2, 15, -14, 0, -12, 29, 28, -2, -24, 2, 9, -7, 1, -28, -5, 3, -22, 14, 30, 27, -17, -27, 25}
};
int selected_graph[31];
int x, start_point;

void display_this(int current_num)
{
  Serial.println(current_num);

  if (current_num < 0) {
    lc.setChar(0, 2, '-', false);
    current_num = -current_num;
  }
  else {
    lc.clearDisplay(0);

  }
  lc.setChar(0, 0, current_num % 10, false);
  lc.setChar(0, 1, current_num / 10, false);


  lc.setChar(0, 7, (char)((sec / 60) / 10), false);
  lc.setChar(0, 6, (char)((sec / 60) % 10), true);
  lc.setChar(0, 5, (char)((sec % 60) / 10), false);
  lc.setChar(0, 4, (char)((sec % 60) % 10), false);
}

void setup() {
  randomSeed(analogRead(0));

  Serial.begin(9600);
  Wire.begin ();

  lc.shutdown(0, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 8);
  /* and clear the display */
  lc.clearDisplay(0);



  //making sure all modules are ready
  for (int i = 0; i < num_of_mod; i++)  {
    while (mod_status[i] == 0 || mod_status[i] == 255) {
      Wire.requestFrom(MOD[i], 1);
      mod_status[i] = Wire.read(); // receive a byte
      lc.setChar(0, 7, (char)(MOD[i] / 10), false);
      lc.setChar(0, 6, (char)(MOD[i] % 10), false);
      lc.setChar(0, 5, '-', false);
      if (mod_status[i] == 0)
        lc.setChar(0, 4, '0', false);
      else
        lc.setChar(0, 4, 'f', false);
      //sending all modules the color for the stage
      for (int i = 0; i < num_of_mod; i++)  {
        Wire.beginTransmission (MOD[i]);
        Wire.write (level[i]); // need to !!!!!!!!!!!!!!!!!!!!!!!!!!11 send more bytes, so the module will know its setup
        Wire.endTransmission ();
      }
    }
  }

  // locker things
  x = random(0, 2);
  start_point = random(-15, 16);


  encoderPosCount = start_point;

  for (int i = 0; i < 31; i++)
  {
    selected_graph[i] = graph_pool[x][i];
  }

  pinMode (pinA, INPUT);
  pinMode (pinB, INPUT);
  pinMode (button, INPUT_PULLUP);
  /*pinMode (ledA, OUTPUT);
    pinMode (ledB, OUTPUT);
    pinMode (ledC, OUTPUT);*/

  /* Read Pin A
    Whatever state it's in will reflect the last position
  */
  pinALast = digitalRead(pinA);
  Serial.begin (9600);
  sum = generate_sum();
  display_this(selected_graph[encoderPosCount + range]); //Display current number in selected graph

  //starting the clock
  lc.setChar(0, 7, (char)((sec / 60) / 10), false);
  lc.setChar(0, 6, (char)((sec / 60) % 10), true);
  lc.setChar(0, 5, (char)((sec % 60) / 10), false);
  lc.setChar(0, 4, (char)((sec % 60) % 10), false);


}

int generate_sum() {
  int sum = 0;
  int n;
  for (int i = 0; i < 3; i++) {
    n = random(0, 31);
    sum += selected_graph[n];
    Serial.println(sum);
  }
  return sum;
}

void loop() {

  if (sec == 0) {
    explode();
  }


  t = millis();

  //counting seconds
  if (t - last_t >= 1000) {

    last_t = t;
    sec--;

    for (int i = 0; i < num_of_mod; i++)  {
      //sending the seconds
      Wire.beginTransmission (MOD[i]);
      Wire.write (sec % 60 % 10);
      Wire.endTransmission ();

      //getting the status
      Wire.requestFrom(MOD[i], 1);
      mod_status[i] = Wire.read(); // receive a byte
      if (mod_status[i] == 2)
        explode();
      if (mod_status[i] == 3)
        sec=sec+30;
    }

    /*if ( ())
      win();*/
    if (let_go) {
      hold_on--;
      if (!hold_on) {
        let_go = 0;
        lc.clearDisplay(0);

      }
    }
    lc.setChar(0, 7, (char)((sec / 60) / 10), false);
    lc.setChar(0, 6, (char)((sec / 60) % 10), true);
    lc.setChar(0, 5, (char)((sec % 60) / 10), false);
    lc.setChar(0, 4, (char)((sec % 60) % 10), false);
  }

  // locker things

  aVal = digitalRead(pinA);
  if (aVal != pinALast) { // Means the knob is rotating
    // if the knob is rotating, we need to determine direction
    // We do that by reading pin B.
    if (digitalRead(pinB) != aVal) {  // Means pin A Changed first - We're Rotating Clockwise
      encoderPosCount ++;
      if (encoderPosCount > range) encoderPosCount = -range;
    } else {// Otherwise B changed first and we're moving CCW
      encoderPosCount--;
      if (encoderPosCount < -range) encoderPosCount = range;
    }

    /*Serial.print ("Rotated: ");
      Serial.print("Encoder Position: ");
      Serial.println(encoderPosCount);*/
    if (stage == 0)
      display_this(selected_graph[encoderPosCount + range]); //Display current number in selected graph

  }
  pinALast = aVal;

  /*
    if (!digitalRead(button)) //Player is Ready
    {
      if (button_reading != 1) {
        delay(100);
        stage++;
        display_this(sum);

        if (stage > 1 && stage < 5)
        {
          all_input = all_input + selected_graph[encoderPosCount + range];
          Serial.print("all_input: ");
          Serial.println(all_input);
          digitalWrite(leds[stage - 2], HIGH);

        }
        if (stage == 5)
        {
          if (all_input == sum)
          {
            Serial.println("You Win");
            lc.setChar(0, 0, '1', true);
            lc.setChar(0, 1, '1', true);
            lc.setChar(0, 2, '1', true);
            lc.setChar(0, 3, '1', true);
          }
        }
      }
      button_reading = 1;

    }
    else {
      button_reading = 0;
    }
  */


  int reading = digitalRead(button);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {

    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        stage++;
        if (stage == 1) {
          display_this(sum);
          hold_on = 2;
          let_go = 1;
        }

        if (stage > 1 && stage < 5)
        {
          all_input = all_input + selected_graph[encoderPosCount + range];
          Serial.print("all_input: ");
          Serial.println(all_input);
          //digitalWrite(leds[stage - 2], HIGH);////////////////////////////////////////////
          if (stage > 1)
            lc.setChar(0, 0, '0', false);
          if (stage > 2)
            lc.setChar(0, 1, '0', false);
          if (stage > 3)
            lc.setChar(0, 2, '0', false);
        }
        if (stage == 4)
        {
          if (all_input == sum)
          {
            win();
          }
          else
          {
            explode();
          }
        }
      }
    }
  }

  lastButtonState = reading;



}


void explode() {
  lc.setChar(0, 4, '8', false);
  lc.setChar(0, 5, '0', false);
  lc.setChar(0, 6, '0', false);
  lc.setChar(0, 7, '8', false);
  delay(1000000000);
}

void win() {
  lc.setChar(0, 7, 'C', false);
  lc.setChar(0, 6, 'L', false);
  lc.setChar(0, 5, 'E', false);
  lc.setChar(0, 4, 'A', false);
  lc.setChar(0, 3, 'A', true);
  lc.setChar(0, 2, 'E', false);
  lc.setChar(0, 1, '0', false);
  lc.setChar(0, 0, '1', true);

  delay(1000000000);
}

bool level_cleared() {
  for (int i = 0; i < num_of_mod; i++)  {
    if (!((mod_status[i] == 3) || (mod_status[i] == 4)))
      return false;
  }
  return true;
}
