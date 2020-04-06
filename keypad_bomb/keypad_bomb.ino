#include <Keypad.h>

String readkey();
int state = 0;
int d = 3;

char hexaKeys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'X', '0', 'Y', 'D'}
};


void setup() {
  Serial.begin(9600);
}

void loop() {
  String b;
  b = readkey();
  Serial.println(b);
  delay(500);
}


String readkey() {
  String a = "qqqqqqqq";
  int loc = 0;


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
        /*Serial.print(i - 2);
        Serial.print("-");
        Serial.print(j - 6);
        Serial.print("\n");*/
        //a[loc] = hexaKeys[j - 6][i - 2];
        
        loc++;
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
        /*Serial.print(i - 6);
        Serial.print("-");
        Serial.print(j - 2);
        Serial.print("\n");*/
        //a[loc] = hexaKeys[i - 6][j - 2];
        
        loc++;
      }
    }
    digitalWrite(i, HIGH);
    delay(d);
  }
  return a;
}
