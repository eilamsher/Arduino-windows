/*
  A 10101010
  B 01010101
  Engine num - PWM,IN1,IN2
  Engine 1 - 3, QA6, QA7
  Engine 2 - 4, QA4, QA5
  Engine 3 - 5, QA2, QA3
  Engine 4 - 6, 7, 8
  Engine 5 - 9, QA1, QA0
  Engine 6 - 23, QB0, QB1
  Engine 7 - 22, QB3, QB2
  Engine 8 - 21, QB5, QB4
  Engine 9 - 20, QB7, QB6


  Engines 0  1  2  /3  4  5  /6 7  8
  Angle p 17 13 5  /25 33 21 /1 9  29
  order   9  21 33 /5  17 29 /1 13 25
*/

const int latchPin = 1; // (74HC595 pin 12)
const int clockPin = 2; // (74HC595 pin 11)
const int dataPin = 0; //  (74HC595 pin 14)

int step_size = 30, data[] = {0, 0, 0, 0, 0, 0, 0, 0, 0}, data2[9];
byte eng_select = 0, temp_read, pwm_pins[] = {3, 4, 5, 6, 9, 23, 22, 21, 20}, eng_order[9] = {4, 7, 3, 8, 2, 1, 6, 0, 5}; //{7, 5, 4, 2, 0, 8, 6, 1, 3};
bool dir[9], eng_dir[8], eng_spec_dir[9] = {0, 1, 0, 0, 1, 0, 0, 1, 1};

int j = 6;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 9; i++) {
    pinMode(pwm_pins[i], OUTPUT);
    //analogWriteFrequency(pwm_pins[i], 18000);
  }
  //analogWriteResolution(12);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);

}

void loop() {
  manual_control();
  //data[0] = -20;
  //data[6]=-250;
  engine_order_organize();
  Serial.println("-----------");
  for (int i = 0; i < 9; i++) {
    Serial.print(data[i]);
    Serial.print(",");
  }
  Serial.println("");
  for (int i = 0; i < 9; i++) {
    Serial.print(data2[i]);
    Serial.print(",");
  }
  Serial.println("");

  //motor_dir_shiftout(data);
  motor_dir_shiftout(data2);

  delay(20);

  /*
    //data[5]=-30;
    data[6]=-30;
    motor_dir_shiftout(data);
    delay(2000);

    data[5]=0;
    data[6]=0;
    //j++;
    motor_dir_shiftout(data);
    delay(3000);

  */
  /*
    for (int i = 0; i < 9; i++) {
    Serial.print(data[i]);
    Serial.print(",");
    }
    Serial.println("");
    delay(50);
  */
}

void engine_order_organize() {
  for (int i = 0; i < 9; i++) {
    data2[i] = data[eng_order[i]];
  }
}

void motor_dir_shiftout(int shift_data[]) {
  int i;

  //get directions
  for (i = 0; i < 9; i++)
    dir[i] = shift_data[i] >= 0;

  for (int i = 0; i < 9; i++) {
    Serial.print(dir[i]);
    Serial.print(",");
  }
  Serial.println("");

  //xor
  for (i = 0; i < 9; i++)
    dir[i] = !dir[i] != !eng_spec_dir[i];

  //organize by engine order
  eng_dir[0] = dir[4];
  for (i = 1; i < 4; i++)
    eng_dir[i] = dir[3 - i];

  for (i = 4; i < 8; i++)
    eng_dir[i] = dir[i + 1];



  digitalWrite(latchPin, 0);
  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(dataPin, 0);
  digitalWrite(clockPin, 0);
  for (i = 7; i >= 0; i--)  {
    send_bit(!eng_dir[i]);
    send_bit(eng_dir[i]);
  }
  //stop shifting

  digitalWrite(clockPin, 0);
  digitalWrite(8, !dir[3]);
  digitalWrite(7, dir[3]);
  digitalWrite(latchPin, 1);

  for (int i = 0; i < 9; i++)
    analogWrite(pwm_pins[i], abs(shift_data[i]));
}


void send_bit(bool val) {
  digitalWrite(clockPin, 0);
  digitalWrite(dataPin, val);
  //Serial.print(val);
  //register shifts bits on upstroke of clock pin
  digitalWrite(clockPin, 1);
  //zero the data pin after shift to prevent bleed through
  digitalWrite(dataPin, 0);
}

void manual_control() {
  if (Serial.available()) {
    temp_read = Serial.read() - 49;
    if ((temp_read > 0) && (temp_read < 10))
      eng_select = temp_read;
    Serial.println(eng_select);
  }
  if (!digitalRead(10))
    data[eng_select] = -step_size;
  else if (!digitalRead(11))
    data[eng_select] = step_size;
  else
    data[eng_select] = 0;
}
