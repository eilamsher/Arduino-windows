//#include "globals.h"
#include <Wire.h>

// mod_status: 0-not ready, 1-playing, 2-lost, 3-win, 4-sleep, 255-disconnect
// my_status is 0 until module is ready

const byte MY_ADDRESS = 44;
byte my_color = 0, message, my_status=0;



#define RED_W 0
#define WHITE_W 1
#define YELLOW_W 2
#define ORANGE_W 3
#define PURPLE_W 4
#define BLUE_W 5
#define DISCONNECTED -1

const byte STAGES = 8;
const byte RED = 1;
const byte YELLOW = 2;
const byte BLUE = 3;
const byte GREEN = 4;
const byte WIRE_AMT = 6;


// globals
int wire_state[WIRE_AMT];
int state_change[WIRE_AMT];
int previous_state[WIRE_AMT];
int history[STAGES + 1][WIRE_AMT];
int solution[STAGES + 1][WIRE_AMT];
int out_wire[] = {8, 10, 9, 11, 13, A1};
int in_wire[] = {2, 3, 4, 5, 6, 7};
int volatile color=0;
bool yellow_moved = true;
int current_stage;
bool second_stage_moved = false;
bool button_pressed = false;
int times_restarted = 0;
// function decelerations
void get_wires();
void print_arr(int* arr, int len);
int count_crossings_in_stage(int stage);
bool wire_moved_in_stage(int wire, int stage);
void switch_wires(int* arr, int a, int b);
int get_wire_connected_to_in_stage(int output_loc, int stage);
void parse_message(byte message);
bool verify_solution ();


void get_wires();
bool is_crossing (int* arr, int A, int B);
bool all_parallel(int stage);

void setup() {
  // put your setup code here, to run once:
    // setting up i2c
  Wire.begin(MY_ADDRESS);                // join i2c bus with address
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  
  Serial.begin(9600);
  for (int i = 0; i < WIRE_AMT; i++) {
    pinMode(in_wire[i], INPUT_PULLUP);
    pinMode(out_wire[i], OUTPUT);
    digitalWrite(out_wire[i], HIGH);
  }
  pinMode(12, INPUT_PULLUP);

  // put your setup code here, to run once:


  get_wires();
  current_stage = 0;

  while (any_disconnected()) {
    Serial.print("Disconnected!!!");
    print_arr(wire_state, WIRE_AMT);
  }
  
  color = read_color();
  
  new_stage();
  color = read_color();
  generate_solution(color);
  while (!verify_solution() && times_restarted < 2)
  {
    delay(50);
    generate_solution(color);
    Serial.println ("Encountered Error, Regenerated Solution");
    times_restarted++;
  }
  if (times_restarted ==2)
  {
    Serial.println("Unknown Error, Reconnect wires randomly");
  }

  print_arr(wire_state, WIRE_AMT);
  for (int i = 0; i < STAGES + 1; i++) {
    for (int j = WIRE_AMT - 1; j >= 0 ; j--) {
      Serial.print(solution[i][j] + 1);
      Serial.print(",");
    }
    Serial.println("");
  }
my_status=1;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (current_stage == 8) { // originally set to 8
    Serial.println("your are winnerrr");
    my_status=3;
    delay(1000000);
  }

  if (state_changed()) {
    print_arr(wire_state, WIRE_AMT);
    if (legal_move()) {
      current_stage++;
      Serial.print("success, you are now in stage ");
      Serial.println(current_stage + 1);
      new_stage();
    }
    else {
      explode();
    }
  }
}

int read_color() {
  while (color == 0){
    delay(10);
    Serial.print(".");
  }
  
  Serial.print("color is ");
  Serial.println(color);
  return color;
}

bool any_disconnected() {
  get_wires();
  for (int i = 0; i < WIRE_AMT; i++)
  {
    if (wire_state[i] == -1)
      return true;
  }
  return false;
}

void explode()
{
  my_status=2;

  Serial.println("BOOK");
  Serial.print("Your stupid answer was: ");
  print_arr(wire_state, WIRE_AMT);
}

void new_stage() {
  memcpy(history[current_stage], wire_state, sizeof(int)*WIRE_AMT);
}

bool state_changed() {
  delay(10);
  if (current_stage == 7) {
    memcpy(previous_state, wire_state, sizeof(int)*WIRE_AMT);
    get_wires();
    for (int i = 0; i < WIRE_AMT; i++) if (previous_state[i] != wire_state[i]) return true;
  }
  if (!digitalRead(12)) {
    //    Serial.print("down!!!");
    if (!button_pressed) {
      button_pressed = true;
      get_wires();
      return true;

    }
    return false;
  }
  delay(30);
  button_pressed = false;
  return false;
}

bool legal_move() {
  int i;
  for (i = 0; i < WIRE_AMT; i++) if (solution[current_stage + 1][i] != wire_state[i]) return false;
  return true;
}

void generate_solution(int color) {
  int stage = 0, i;
  memcpy(solution[stage], history[0], sizeof(int)*WIRE_AMT);

  //////////////////////////////////////////////// RED //////////////////////////////////////////////////////
  if (color == RED) {
    // write stage 1
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    switch_wires(solution[stage], RED_W, PURPLE_W);


    // write stage 2
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    if (solution[stage][YELLOW_W] == 0)
      switch_wires(solution[stage], YELLOW_W, PURPLE_W);
    else
      switch_wires(solution[stage], YELLOW_W, get_wire_connected_to_in_stage(solution[stage][YELLOW_W] - 1, stage - 1));

    // write stage 3
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    switch_wires(solution[stage], ORANGE_W, WHITE_W);

    // write stage 4
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    switch_wires(solution[stage], RED_W, get_wire_connected_to_in_stage(4, stage - 1));


    // write stage 5
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    if (abs(solution[stage][ORANGE_W] - solution[stage][RED_W]) == 1) {
      switch_wires(solution[stage], ORANGE_W, PURPLE_W);
    }
    else {
      switch_wires(solution[stage], ORANGE_W, YELLOW_W);
    }

    // write stage 6
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    switch_wires(solution[stage], YELLOW_W, BLUE_W);

    // write stage 7
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    if (abs(solution[stage][WHITE_W] - solution[stage][PURPLE_W]) == 1) {
      switch_wires(solution[stage], WHITE_W, RED_W);
    }

    // write stage 8
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);

    if (solution[stage][ORANGE_W] % 2 == 0) {
      solution[stage][WHITE_W] = -1;
    }
    else {
      solution[stage][ORANGE_W] = -1;
    }
  }

  //////////////////////////////////////////////// YELLOW ////////////////////////////////////////////////
  if (color == YELLOW) {
    // write stage 1
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    if (is_crossing(history[0], PURPLE_W, ORANGE_W)) {
      switch_wires(solution[stage], RED_W, YELLOW_W);
    }
    else {
      switch_wires(solution[stage], PURPLE_W, ORANGE_W);
    }

    // write stage 2
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    switch_wires(solution[stage], RED_W, BLUE_W);

    // write stage 3
    stage++;

    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    switch_wires(solution[stage], YELLOW_W, get_wire_connected_to_in_stage(2, (stage - 1)));

    // write stage 4
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    switch_wires(solution[stage], WHITE_W, RED_W);



    // write stage 5
    stage++;

    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    int temp_array[WIRE_AMT];
    memcpy(temp_array, solution[stage - 1], sizeof(int)*WIRE_AMT);
    switch_wires(temp_array, YELLOW_W, PURPLE_W);
    if (is_crossing(temp_array, PURPLE_W, WHITE_W))
    {
      switch_wires(solution[stage], RED_W, YELLOW_W);
    }
    else {
      switch_wires(solution[stage], PURPLE_W, YELLOW_W);
    }

    // write stage 6
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    if (wire_moved_in_stage(YELLOW_W, 1)) {
      switch_wires(solution[stage], RED_W, PURPLE_W);
    }
    else {
      switch_wires(solution[stage], ORANGE_W, PURPLE_W);
    }

    // write stage 7
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    switch_wires(solution[stage], WHITE_W, BLUE_W);


    // write stage 8
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);

    if (all_parallel(stage - 1)) {
      solution[stage][YELLOW_W] = DISCONNECTED; // disconnect ORANGE_W
    }
    else {
      solution[stage][RED_W] = DISCONNECTED; // disconnect WHITE_W
    }
  }




  //////////////////////////////////////////// BLUE //////////////////////////////////////////////////
  if (color == BLUE) {
    // write stage 1
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    switch_wires(solution[stage], WHITE_W, YELLOW_W);
    switch_wires(solution[stage], RED_W, BLUE_W);

    // write stage 2
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    if ( count_crossings_in_stage(stage) > 4) {
      Serial.println("There are more than 4 crossings");
      solution[stage][YELLOW_W] = YELLOW_W;
      solution[stage][RED_W] = RED_W;
      solution[stage][WHITE_W] = WHITE_W;
      solution[stage][ORANGE_W] = ORANGE_W;
      solution[stage][PURPLE_W] = PURPLE_W;
      solution[stage][BLUE_W] = BLUE_W;
    }

    // write stage 3
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    int orig_red_loc = solution[stage][RED_W];
    solution[stage][RED_W] = DISCONNECTED;

    // write stage 4
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    if (solution[stage][PURPLE_W] > 3) {
      if (get_wire_connected_to_in_stage(1, stage) == DISCONNECTED) {
        solution[stage][PURPLE_W] = 1;
      }
      else {
        switch_wires(solution[stage], PURPLE_W, get_wire_connected_to_in_stage(1, stage));
      }
    }

    // write stage 5
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    if (get_wire_connected_to_in_stage(ORANGE_W, stage) == DISCONNECTED) {
      solution[stage][YELLOW_W] = ORANGE_W;
    }
    else {
      switch_wires(solution[stage], YELLOW_W, get_wire_connected_to_in_stage(ORANGE_W, stage));
    }

    // write stage 6
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    switch_wires(solution[stage], WHITE_W, PURPLE_W);

    // write stage 7
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    if (get_wire_connected_to_in_stage(orig_red_loc, stage) == DISCONNECTED) {
      solution[stage][RED_W] = orig_red_loc;
    }
    else {
      switch_wires(solution[stage], RED_W, get_wire_connected_to_in_stage(orig_red_loc, stage));
    }


    // write stage 8
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);

    if (is_crossing(solution[stage], PURPLE_W, YELLOW_W) || is_crossing(solution[stage], WHITE_W, RED_W)) {
      solution[stage][RED] = DISCONNECTED;
    }
    else {
      solution[stage][ORANGE_W] = DISCONNECTED;
    }
  }


  //////////////////////////////////////////// GREEN //////////////////////////////////////////////////
  if (color == GREEN) {
    // write stage 1
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    if (abs(solution[stage][ORANGE_W] - solution[stage][YELLOW_W]) == 1)
    {
      switch_wires(solution[stage], ORANGE_W, YELLOW_W);
      yellow_moved = true;
      Serial.println("Yellow did move");
    }

    else
    {
      yellow_moved = false;
    }


    // write stage 2
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    if (abs(solution[stage][WHITE_W] - solution[stage][YELLOW_W]) == 1)
    {
      switch_wires(solution[stage], PURPLE_W, YELLOW_W);
      yellow_moved = true;
      second_stage_moved = true;
      Serial.println("Second stage DID move");
    }


    // write stage 3
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    if (is_crossing(solution[stage], BLUE_W, ORANGE_W))
    {
      switch_wires(solution[stage], ORANGE_W, RED_W);
    }

    // write stage 4
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    if (is_crossing(history[0], BLUE_W, ORANGE_W)) {
      switch_wires(solution[stage], RED_W, ORANGE_W);
    }

    // write stage 5
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    if (yellow_moved == true)
    {
      solution[stage][WHITE_W] = DISCONNECTED;
    }

    // write stage 6
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
        int orig_red_loc = solution[stage][RED_W];

      switch_wires(solution[stage], RED_W, get_wire_connected_to_in_stage(orig_red_loc, stage));

    // write stage 7
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    solution[stage][WHITE_W] = DISCONNECTED;
    solution[stage][YELLOW_W] = DISCONNECTED;
    solution[stage][ORANGE_W] = DISCONNECTED;
    solution[stage][PURPLE_W] = DISCONNECTED;



    // write stage 8
    stage++;
    memcpy(solution[stage], solution[stage - 1], sizeof(int)*WIRE_AMT);
    if (second_stage_moved == true)
    {
      solution[stage][RED_W] = DISCONNECTED;
    }
    else
    {
      solution[stage][YELLOW_W] = YELLOW_W;
      solution[stage][BLUE_W] = DISCONNECTED;
    }
  }

}

int count_crossings_in_stage(int stage) {
  int cnt = 0;
  for (int i = 0; i < WIRE_AMT; i++) {
    for (int j = i + 1; j < WIRE_AMT; j++) {
      if (is_crossing(solution[stage], i, j))
        cnt++;
    }
  }
  return cnt;
}

bool wire_moved_in_stage(int wire, int stage) {
  return (solution[stage][wire] != solution[stage - 1][wire]);
}

int get_wire_connected_to_in_stage(int output_loc, int stage) {
  int i;
  for (i = 0; i < WIRE_AMT; i++) {
    if (solution[stage][i] == output_loc) {
      return i;
    }
  }
  return -1;
}

void switch_wires(int* arr, int a, int b) {
  int temp;
  // if the switch is with a disconnected wire:
  if (a == -1) {
    arr[a] =  b;
    arr[b] = -1;
  }
  if (b == -1) {
    arr[a] =  a;
    arr[b] = -1;
  }

  temp = arr[a];
  arr[a] = arr[b];
  arr[b] = temp;
}

bool verify_solution ()
{
  int checkbox[WIRE_AMT];
  for (int i = 0; i < WIRE_AMT; i++)
  {
    checkbox[i] = 0;
  }
  for (int j = 0; j < STAGES; j++)
  {
    for (int i = 0; i < WIRE_AMT; i++)
    {
      int plugged_into = (solution[j][i]);
      if (plugged_into != -1)
      {
        if (checkbox[plugged_into] == 0)
          checkbox[i] = 1;
        else
          return false;
      }
    }
    for (int i = 0; i < WIRE_AMT; i++)
      checkbox[i] = 0;
  }
  return true;
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

bool is_crossing (int* arr, int A, int B) {
  if (A < B && (arr[B] < arr[A]))
    return true;
  else if ((A > B) && (arr[B] > arr[A]))
    return true;
  return false;
}

bool all_parallel(int stage) {
  for (int i = 0; i < WIRE_AMT; i++)
  {
    if (solution[stage][i] != i)
      return false;
  }
  return true;
}

void print_arr(int* arr, int len) {
  for (int i = len - 1; i >= 0; i--) {
    Serial.print(arr[i] + 1);
    Serial.print(",");
  }
  Serial.println("");
  Serial.println("");
}


void receiveEvent(int howMany) {
  if(color == 0)
  {
    color = Wire.read();
  }
  else
  {
    message = Wire.read();
    parse_message(message);
  }
}

// make and action according to the message recieved
void parse_message(byte message){
}


void requestEvent() {
  Wire.write(my_status);
}
