const byte WIRE_AMT = 6;
int wire_state[WIRE_AMT];

int out_wire[] = {8,10,9,11,A0};
int in_wire[] = {2,3,4,5,6,7};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 0; i < WIRE_AMT; i++) {
    pinMode(in_wire[i], INPUT_PULLUP);
    pinMode(out_wire[i], OUTPUT);
    digitalWrite(out_wire[i], HIGH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
get_wires();
//print_arr(*wire_state);
  Serial.println(wire_state[4]);

delay(1000);
}

void get_wires() {


  for (int i = 0; i < WIRE_AMT; i++) {


    wire_state[i] = -1;
    digitalWrite(out_wire[i], LOW);
    for (int j = 0; j < WIRE_AMT; j++) {

      if (!digitalRead(in_wire[j]))
        wire_state[i] = j;
    }
    digitalWrite(out_wire[i], HIGH);

  }
}

void print_arr(int* arr) {
  for (int i = 0; i < WIRE_AMT; i++) {
    Serial.print(arr[i] + 1);
    Serial.print(",");
  }
  Serial.println("");
  Serial.println("");
}
