//#include "globals.h"




// TODO: add history

const byte STAGES = 9;
const byte YELLOW = 1;
const byte WIRE_AMT = 5;


// globals
int current_state[WIRE_AMT];
int state_change[WIRE_AMT];
int previous_state[WIRE_AMT];
int history[STAGES][WIRE_AMT];
int solution[STAGES][WIRE_AMT];
int in_wire[] = {8, 9, 10, 11, 12};
int out_wire[] = {2, 3, 4, 5, 6};
int current_stage;
bool button_pressed = false;

// function decelerations
void get_wires();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 0; i < WIRE_AMT; i++) {
    pinMode(in_wire[i], INPUT_PULLUP);
    pinMode(out_wire[i], OUTPUT);
    digitalWrite(out_wire[i], HIGH);
  }
      pinMode(7, INPUT_PULLUP);

  // put your setup code here, to run once:


  get_wires();
  current_stage = 0;
  new_stage();
  generate_solution(YELLOW);

print_arr(current_state, WIRE_AMT);
}

void loop() {
  // put your main code here, to run repeatedly:
if(current_stage==8){
      Serial.println("your are winnerrr");
delay(10000);
}
  
  if (state_changed()) {
    print_arr(current_state, WIRE_AMT);
    if (legal_move()) {
      current_stage++;
      new_stage();
    }
    else {
      explode();
    }
  }

  //  get_wires();
  //  for (int i = 0; i < wire_num; i++) {
  //    Serial.print(current_state[i]+1);
  //    Serial.print(",");
  //
  //  }
  //  Serial.println(" ");
  //
  //  delay(1000);

}

void explode() {
  Serial.println("BOOK");
}

void new_stage() {
  memcpy(history[current_stage], current_state, sizeof(int)*WIRE_AMT);
}

bool state_changed() {
  if (current_stage == 7) {
    memcpy(previous_state, current_state, sizeof(int)*WIRE_AMT);
    get_wires();
    for (int i = 0; i < WIRE_AMT; i++) if (solution[current_stage + 1][i] != current_state[i]) return true;
  }
  if (!digitalRead(7)) {
    if (! button_pressed) {
      button_pressed = true;
      get_wires();
      return true;
    }
    return false;
  }
  button_pressed = false;
  return false;
}

bool legal_move() {
  int i;
  for (i = 0; i < WIRE_AMT; i++) if (solution[current_stage + 1][i] != current_state[i]) return false;
  return true;
}

void generate_solution(int color) {
  int stage = 0, i;

  memcpy(solution[stage], history[0], sizeof(int)*WIRE_AMT);
  if (color == YELLOW) {
    // write stage 1
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    if (is_crossing(5, 4, 0)) {
      switch_wires(1, 3, stage);
    }
    else {
      switch_wires(5, 4, stage);
    }

    // write stage 2
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    switch_wires(1, 5, stage);

    // write stage 3
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    switch_wires(3, get_wire_connected_to(3, stage - 1), stage);

    // write stage 4
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    switch_wires(2, 1, stage);

    // write stage 5
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    if (not is_crossing(3, 2, stage - 1)) {
      switch_wires(5, 3, stage);
    }
    else {
      switch_wires(1, 3, stage);
    }

    // write stage 6
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    if (wire_moved_in_stage(3, 1)) {
      switch_wires(1, 5, stage);
    }
    else {
      switch_wires(4, 5, stage);
    }

    // write stage 7
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    switch_wires(2, 3, stage);

    // write stage 8
    bool any_wire_connected_straight = false;
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    if (all_parallel()) {
      solution[stage][3] = -1; // disconnect 3
    }
    else {
      solution[stage][1] = -1; // disconnect 1
    }

  }
}

bool wire_moved_in_stage(int wire, int stage) {
  return (solution[stage][wire] != solution[stage - 1][wire]);
}

int get_wire_connected_to(int output_loc, int stage) {
  int i;
  for (i = 0; i < WIRE_AMT; i++) if (solution[stage][i] != output_loc) return i;
}

void switch_wires(int a, int b, int stage) {
  int temp;

  temp = solution[stage][a];
  solution[stage][a] = solution[stage][b];
  solution[stage][b] = temp;
}

void get_wires() {


  for (int i = 0; i < WIRE_AMT; i++) {


    current_state[i] = -1;
    digitalWrite(out_wire[i], LOW);
    for (int j = 0; j < WIRE_AMT; j++) {

      if (!digitalRead(in_wire[j]))
        current_state[i] = j;
    }
    digitalWrite(out_wire[i], HIGH);

  }
}

bool is_crossing (int A, int B, int stage) {
  if (A < B && (history[stage][B - 1] < history[stage][A - 1]))
    return true;
  else if ((A > B) && (history[stage][B - 1] > history[stage][A - 1]))
    return true;
  return false;
}

bool all_parallel() {
  for (int i = 0; i < WIRE_AMT; i++)
  {
    if (current_state[i] != i)
      return false;
  }
  return true;
}

void print_arr(int* arr, int len) {
  for (int i = 0; i < len; i++) {
    Serial.print(arr[i]+1);
    Serial.print(",");
  }
}
