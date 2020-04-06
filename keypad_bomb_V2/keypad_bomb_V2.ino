unsigned long preMillis = 0;
int sec = 10;

void readkey(bool* a);
int d = 10;
bool b[16];
bool pre[16];

void setup() {
  Serial.begin(9600);
}

void loop() {
  if(sec==0){
        Serial.print("BOOM!!!!!");
        delay(10000000000000000000000);
  }
  if (millis() - preMillis >= 1000) {
    preMillis=millis();
    sec--;
    Serial.print(sec/60);
    Serial.print(":");
    Serial.print(sec%60);
    Serial.print("\n");
  }
  for (int i = 0; i <= 15; i++) {
    pre[i] = b[i];
    b[i] = false;
  }
  //readkey(b);













  /*for (int i = 0; i <= 15; i++) {
    if (b[i]) {
      Serial.print(i + 1);
      Serial.print(" ");
    }

    }
    Serial.print("\n");
    delay(500);*/
}




void readkey(bool* a) {


  //first run
  for (int i = 2; i <= 5; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  for (int i = 6; i <= 9; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  for (int i = 2; i <= 5; i++) {
    digitalWrite(i, LOW);
    delay(d);
    for (int j = 6; j <= 9; j++) {
      delay(d);
      if (digitalRead(j) == LOW) {
        //a[loc] = hexaKeys[j - 6][i - 2];
        a[(j - 6) * 4 + i - 2] = true;
      }
    }
    digitalWrite(i, HIGH);
    delay(d);
  }



  //second run
  for (int i = 6; i <= 9; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  for (int i = 2; i <= 5; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  for (int i = 6; i <= 9; i++) {
    digitalWrite(i, LOW);
    delay(d);
    for (int j = 2; j <= 5; j++) {
      delay(d);

      if (digitalRead(j) == LOW) {

        //a[loc] = hexaKeys[i - 6][j - 2];
        a[(j - 2) + (i - 6) * 4] = true;
      }
    }
    digitalWrite(i, HIGH);
    delay(d);
  }
}
