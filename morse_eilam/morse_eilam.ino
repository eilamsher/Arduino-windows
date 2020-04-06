const int short_delay = 300, long_delay = 2000;
long t = 0, last_t = 0;


byte current_char_idx = 0, led_count = 0, on_off = 0, switch_state[5], old_switch_state[5], switch_input[5], current_cell = 0;
const byte red_pin = 3, blue_pin = 6, green_pin = 5;

const byte switch_pin[] = {2, 4, 7, 8, 9, 10, 11, 12}, alt_pin = 13; //up down

const byte down_1[] = {0, 0, 0, 0, 0}, down_2[] = {0, 0, 0, 0, 0}, down_3[] = {0, 0, 0, 0, 0}, down_4[] = {0, 0, 0, 0, 0};
const byte current_led[] = {1, 5, 2, 3};
const byte color_range[7][3] = {{0, 0, 0}, {255, 0, 0}, {0, 255, 255}, {255, 255, 0}, {0, 255, 0}, {0, 0, 255}, {255, 0, 255}}; //orange_color[]={255,128,0}, yellow_color[]={255,255,0}, purple_color[]={153,51,255}, red_color[]={255,0,0}, green_color[]={0,255,0}, blue_color[]={0,0,255};

enum directions {
  NONE, UP, DOWN, ALT_UP, ALT_DOWN
};

enum colors {
  BLACK, RED, CYAN, YELLOW, GREEN, BLUE, PINK
};

void array_assign() ;
void read_switch();
byte get_switch_diff();
void explode();
void update_switch();
void write_led();


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(alt_pin, INPUT);
  for (int i = 0; i < 8; i++) {
    pinMode(switch_pin[i], INPUT_PULLUP);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  array_assign();
  read_switch();
  byte switch_idx = get_switch_diff();

  if (switch_idx != 255) {
    if ( switch_idx != current_char_idx)
      explode();

    else {
      if (switch_state[current_char_idx + 1] == 0) {
        update_switch();
        for (int i = 0; i < 5; i++) {
          Serial.print(switch_input[i]);


        }
        Serial.println(" change");
      }
    }
  }
  t = millis();
  if (t - last_t > short_delay) {
    last_t = t;
    write_led();
  }



}



void write_led() {
  /*for (int i = 0; i < 5; i++) {
    Serial.print(switch_state[i]);
    Serial.print(",");
    }
    Serial.println("");*/

  if (on_off) {
    on_off = !on_off;
    analogWrite(red_pin, 0);
    analogWrite(blue_pin, 0);
    analogWrite(green_pin, 0);
    if (led_count % 4 == 0)
      last_t = last_t + long_delay - short_delay;
  }
  else {
    on_off = !on_off;
    analogWrite(red_pin, color_range[current_led[led_count % 4]][0]);
    analogWrite(blue_pin, color_range[current_led[led_count % 4]][2]);
    analogWrite(green_pin, color_range[current_led[led_count % 4]][1]);
    led_count++;
  }
}

void read_switch() {
  switch_state[0] = digitalRead(alt_pin);
  switch_state[1] = -digitalRead(switch_pin[0]) + digitalRead(switch_pin[1]);
  switch_state[2] = -digitalRead(switch_pin[2]) + digitalRead(switch_pin[3]);
  switch_state[3] = -digitalRead(switch_pin[4]) + digitalRead(switch_pin[5]);
  switch_state[4] = -digitalRead(switch_pin[6]) + digitalRead(switch_pin[7]);
  delay(2);
}

byte get_switch_diff() {
  for (int i = 4; i > 0 ; i--) {
    if (old_switch_state[i] != switch_state[i])
      return i - 1;
  }

  return 255;
}

void array_assign() {
  for (int i = 0; i < 5; i++)
    old_switch_state[i] = switch_state[i];
}

void update_switch() {

  if (old_switch_state[0] == 1) {
    if (old_switch_state[current_char_idx + 1] == 1)
      switch_input[current_cell % 5] = 3;
    else
      switch_input[current_cell % 5] = 4;
  }
  else {
    if (old_switch_state[current_char_idx + 1] == 1)
      switch_input[current_cell % 5] = 1;
    else
      switch_input[current_cell % 5] = 2;
  }

  current_cell++;
}

void explode() {
  Serial.println(" book");

}
