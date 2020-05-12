

int keys[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
byte rows[] = {8,7,6,5}; //{15, 14, 13, 12};
byte cols[] =  {9, 10, 11, 12};//{16, 17, 18, 19};
byte arr[4][4];


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(read_keypad());
  //Serial.print(read_keypad());
  read_keypad2();
  //print_arr();
  Serial.println("------------------------");
  delay(300);
}

int read_keypad() {
  int a = 0, b = 0;
  for (int i = 0; i < 4; i++) {
    pinMode(rows[i], OUTPUT);
    pinMode(cols[i], INPUT_PULLUP);
    digitalWrite(rows[i], LOW);
  }
  for (int i = 0; i < 4; i++) {
    if (!digitalRead(cols[i])) {
      Serial.print ("cols ");
      Serial.print (i);
      Serial.print (",");
      a = i;
    }
  }

  for (int i = 0; i < 4; i++) {
    pinMode(cols[i], OUTPUT);
    pinMode(rows[i], INPUT_PULLUP);
    digitalWrite(cols[i], LOW);
  }
  for (int i = 0; i < 4; i++) {
    if (!digitalRead(rows[i])) {
      Serial.print (" rows ");
      Serial.print (i);
      Serial.print (",");
      b = i;
    }
  }
  Serial.print (" button ");
  Serial.print (keys[a][b]);

  /*

  */

  /*
    for (int i = 0; i < 4; i++) {
      pinMode(cols[i], OUTPUT);
      pinMode(rows[i], INPUT_PULLUP);
      digitalWrite(cols[i], HIGH);
    }
    for (int i = 0; i < 4; i++) {
      digitalWrite(cols[i], LOW);
      delay(5);
      for (int j = 0; j < 4; j++) {
        if (!digitalRead(rows[j])) {
          digitalWrite(cols[i], LOW);
          Serial.print (keys[i][j]);
          Serial.print (",");
        }
        delay(5);
      }
      digitalWrite(cols[i], HIGH);
      delay(5);
    }
  */
  //return -1;
}

void read_keypad2() {
  for (int i = 0; i < 4; i++) {
    pinMode(rows[i], OUTPUT);
    pinMode(cols[i], INPUT_PULLUP);
    digitalWrite(rows[i], LOW);
  }
  for (int i = 0; i < 4; i++) {
    digitalWrite(rows[i], LOW);
    delay(5);
    for (int j = 0; j < 4; j++) {
      if (!digitalRead(cols[j])) {
        digitalWrite(rows[i], LOW);
        Serial.print (keys[i][j]);
        Serial.print (",");
      }
      delay(5);
    }
    digitalWrite(rows[i], HIGH);
    delay(5);
  }
}


void read_keypad_arr() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(rows[i], LOW);
    delay(5);
    for (int j = 0; j < 4; j++) {
      arr[i][j] = !digitalRead(cols[j]);
      delay(5);
    }
    digitalWrite(rows[i], HIGH);
    delay(5);

  }
  //return -1;
}

void print_arr() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      Serial.print(arr[i][j]);
      Serial.print(",");
    }
    Serial.println("");
  }
}
