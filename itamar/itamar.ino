const byte WIRE_AMT = 6;

int pins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
int len = 11;

int wire_state[11];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  /*
  for (int i = 0; i < len; i++) {
    pinMode(pins[i], INPUT_PULLUP);
  }*/
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
/*
  
    get_wires();
    //print_arr(*wire_state);

    for (int i = 0; i < len; i++) {
    Serial.print(pins[i]);
    Serial.print(",");
    }
    Serial.println("");
    for (int i = 0; i < len; i++) {
    Serial.print(wire_state[i]);
    Serial.print(",");
    }
    Serial.println("");
    Serial.println("");
  */
digitalWrite(9,LOW);
delay(300);
digitalWrite(9,HIGH);

digitalWrite(10,LOW);
delay(300);
digitalWrite(10,HIGH);

digitalWrite(11,LOW);
delay(300);
digitalWrite(11,HIGH);
delay(1000);
}

void get_wires() {


  for (int i = 0; i < len; i++) {
    wire_state[i] = (!digitalRead(i));

  }
}
