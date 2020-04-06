byte state, last_state;
unsigned long t = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(0, OUTPUT);
  pinMode(1, INPUT_PULLUP);
  state = digitalRead(1);
  last_state = state;
}

void loop() {
  // put your main code here, to run repeatedly:
  state = digitalRead(1);
  if (state != last_state) {
    t = millis();
    digitalWrite(0, HIGH);
  }
  last_state = state;
  if (millis() - t > 2000) {
    digitalWrite(0, LOW);
  }
}
