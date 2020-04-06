int in_wire[] = {8, 9, 10, 11, 12};
int out_wire[] = {2, 3, 4, 5, 6};
const byte wire_num = 5;
int current_state[wire_num];

void get_wires();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 0; i < wire_num; i++) {
    pinMode(in_wire[i], INPUT_PULLUP);
    pinMode(out_wire[i], OUTPUT);
    digitalWrite(out_wire[i], HIGH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  get_wires();
  for (int i = 0; i < wire_num; i++) {
    Serial.print(current_state[i] + 1);
    Serial.print(",");

  }
  Serial.println(" ");
  if (analogRead(A7) < 1000)
    Serial.println("confirm on");
  else
    Serial.println("confirm off");

  delay(1000);
}



void get_wires() {
  for (int i = 0; i < wire_num; i++) {
    current_state[i] = -1;
    digitalWrite(out_wire[i], LOW);
    for (int j = 0; j < wire_num; j++) {
      if (!digitalRead(in_wire[j]))
        current_state[i] = j;
    }
    digitalWrite(out_wire[i], HIGH);

  }
}
