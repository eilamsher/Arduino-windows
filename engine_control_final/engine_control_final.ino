/*
byte pins[5][3] = {
  {3, 2, 4},
  {6, 7, 8},
  {5, A4, A5},
  {9, A2, A3},
  {10, A1, A0}
};
byte eng_order[5] = {0, 1, 2, 3, 4};
*/
byte pins[5][3] = {
  {3, 2, 4},
  {6, 7, 8},
  {5, A4, A5},
  {9, A3, A2},
};

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 3; j++)
      pinMode(pins[i][j], OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int a = 40;
  /*
    for (int i = 0; i < 5; i++) {
    analogWrite(pins[i][0], abs(a));
    digitalWrite(pins[i][1], a >= 0);
    digitalWrite(pins[i][2], a < 0);
    delay(2000);
    analogWrite(pins[i][0], 0);
    }
    delay(10000);
  */
  int i = 3;
  analogWrite(pins[i][0], abs(a));
  digitalWrite(pins[i][1], a >= 0);
  digitalWrite(pins[i][2], a < 0);
  delay(2000);
  analogWrite(pins[i][0], 0);
  delay(2000);

}
