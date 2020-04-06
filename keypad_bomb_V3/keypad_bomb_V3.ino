//TODO:
//define variable name and functionality in rules and game logic
//expand rules and logic to more game type (currently working only with 3 keys)

//#include "globals.h"

#define FAIL -1
#define ACTIVE 0
#define DONE 1
#define CHAR_AMT 16

// -----------structs---------------------
struct gameMove {
  int key = -2;
  bool down = false;
};

struct KeyPadState {
  bool keys[CHAR_AMT];
};

struct ModuleIn {
  int t;
  int mode; // 0 if inactive, otherwise active
};

struct ModuleOut {
  int gameState;
};


// -----------functions-------------------
ModuleIn getGlobals(ModuleOut); // should be in globals.h
bool isClear(KeyPadState kp);
gameMove readMove(bool* oldKP, bool* newKP);
KeyPadState readKeyPad();
void init_keys(bool* a);
void validateSolvable();
//    util funcs
void print_arr(bool* p, int s);

// ------------globals-------------------
ModuleIn global;
ModuleOut output;
KeyPadState keyPadStateOld, keyPadStateNew;
int moduleStage = 1;
unsigned long preMillis = 0;
int sec = 300;
int Seq;
int history[5] = { -1, -1, -1, -1, -1};
bool uneed[16];
int S[5];
int lastTime;

int d = 8;
bool currentPress[16];
bool beforePress[16];

void print_arr(bool* p, int s) {
  for (int i = 0; i < s; i++)  {
    for (int j = 0; j < s; j++) {
      Serial.print(p[i * s + j]);
      Serial.print(",");
    }
    Serial.print("\n");
  }
  Serial.println("---------------------------------------");
}

void setup() {
  // put your setup code here, to run once:
  randomSeed(analogRead(A0));
  keyPadStateNew = readKeyPad();
  keyPadStateOld = keyPadStateNew;
  Serial.begin(9600);
  random_seq(S);
  Serial.print(">>>>> ");

  Serial.println(S[moduleStage - 1]);
}

void loop() {
  gameMove currMove;
  global = getGlobals(output);
  if (global.mode > ACTIVE) {
    // if there was a fail, wait for keypad to be cleared
    if (output.gameState == FAIL) {
      Serial.println("wait for keypad to clear...");
      while (!isClear(readKeyPad()));
      moduleStage = 1;
      output.gameState = ACTIVE;
      random_seq(S);
    }

    // read key pad state
    keyPadStateNew = readKeyPad();
    currMove = readMove(keyPadStateOld, keyPadStateNew);
    //    Serial.println("old:");
    //    print_arr(keyPadStateOld.keys, 4);
    //    Serial.println("new:");
    //    print_arr(keyPadStateNew.keys, 4);
    keyPadStateOld = keyPadStateNew;
    if (currMove.key == -2)
      return;
    else if (currMove.key == -1) {
      output.gameState = FAIL;
      Serial.println("BOOK!! 2 move in same turn");
    }
    else {
      Serial.print("move (");
      Serial.print(currMove.key+1);
      Serial.print(",");
      Serial.print(currMove.down);
      Serial.println(")");
      output.gameState = updateModuleState(currMove);
    }
    Serial.print(">>>>> ");
    Serial.println(S[moduleStage - 1]);
  }
}

void random_seq(int* seqe) {
  for (int i = 0; i < 5; i++) {
    seqe[i] = random(1, 6);

  }
}

gameMove readMove(KeyPadState oldKP, KeyPadState newKP) { // if 2 moves done return key as -1
  gameMove moveDone;
  moveDone.key = -2;

  for (int i = 0; i < CHAR_AMT; i++) {
    if (oldKP.keys[i] != newKP.keys[i]) { // on key change
      if (moveDone.key != -2) {
        moveDone.key = -1;
        return moveDone;
      }
      gameMove mv;
      moveDone.key = i;
      moveDone.down = bool(oldKP.keys[i] < newKP.keys[i]);
    }
  }
  return moveDone;
}

bool isClear(KeyPadState kp) {
  for (int i; i < CHAR_AMT; i++)
    if (kp.keys[i])
      return false;
  return true;
}

ModuleIn getGlobals(ModuleOut output) {
  if (sec == 0 || output.gameState == FAIL) {
    Serial.print("BOOM!!!!!");
    delay(10000000000000000000000);
  }
  if (millis() - preMillis >= 1000) {
    preMillis = millis();
    sec--;
    Serial.print(sec / 60);
    Serial.print(":");
    Serial.print(sec % 60);
    Serial.print("\n");
    ModuleIn in = {sec, 1};
    return in;
  }
}

KeyPadState readKeyPad() {
  KeyPadState ret;
  init_keys(ret.keys);

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
        ret.keys[(j - 6) * 4 + i - 2] = true;
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
        ret.keys[(j - 2) + (i - 6) * 4] = true;
      }
    }
    digitalWrite(i, HIGH);
    delay(d);
  }

  return ret;
}

void init_keys(bool* a) {
  for (int i = 0; i < CHAR_AMT; i++)
    a[i] = false;
}


int releaseSeq()
{
  int preciseSec = (lastTime % 60) % 10;
  if ((preciseSec == 0) || (preciseSec == 3) || (preciseSec == 8)) {
    return 123;
  }
  if (preciseSec == 1) {
    return 132;
  }
  if ((preciseSec == 2) || (preciseSec == 6)) {
    return 321;
  }
  if ((preciseSec == 4) || (preciseSec == 9)) {
    return 213;
  }
  if (preciseSec == 5)
    return 312;

  return 231;
}

void solution(bool* uneed)
{
  switch (moduleStage) {
    case 1:
      switch (S[moduleStage - 1]) {
        case 1:
          uneed[6] = true;
          break;
        case 2:
          uneed[1] = true;
          uneed[2] = true;
          uneed[5] = true;
          uneed[6] = true;
          uneed[9] = true;
          uneed[10] = true;
          uneed[13] = true;
          uneed[14] = true;
          break;
        case 3:
          uneed[14] = true;
          break;
        case 4:
          uneed[7] = true;
          uneed[11] = true;
          break;
        case 5:
          uneed[0] = true;
          break;
      }
      break;
    case 2:
      switch (S[moduleStage - 1]) {
        case 1:
          uneed[13] = true;
          break;
        case 2:
          uneed[4] = true;
          uneed[5] = true;
          uneed[6] = true;
          uneed[7] = true;
          uneed[12] = true;
          uneed[13] = true;
          uneed[14] = true;
          uneed[15] = true;
          break;
        case 3:
          uneed[1] = true;
          break;
        case 4:
          uneed[0] = true;
          uneed[1] = true;
          uneed[2] = true;
          uneed[3] = true;
          uneed[4] = true;
          uneed[5] = true;
          uneed[6] = true;
          uneed[7] = true;
          break;
        case 5:
          uneed[0] = true;
          uneed[2] = true;
          uneed[3] = true;
          uneed[4] = true;
          uneed[6] = true;
          uneed[7] = true;
          uneed[8] = true;
          uneed[10] = true;
          uneed[11] = true;
          uneed[12] = true;
          uneed[14] = true;
          uneed[15] = true;
          break;
      }
      break;
    case 3:
      switch (S[moduleStage - 1]) {
        case 1:
          uneed[4] = true;
          uneed[5] = true;
          uneed[6] = true;
          uneed[7] = true;
          uneed[8] = true;
          uneed[9] = true;
          uneed[10] = true;
          uneed[13] = true;
          uneed[11] = true;
          uneed[12] = true;
          uneed[14] = true;
          uneed[15] = true;
          break;
        case 2:
          uneed[9] = true;
          uneed[12] = true;
          break;
        case 3:
          uneed[0] = true;
          uneed[3] = true;
          uneed[12] = true;
          uneed[15] = true;
          break;
        case 4:
          uneed[4] = true;
          uneed[5] = true;
          break;
        case 5:
          uneed[0] = true;
          uneed[1] = true;
          uneed[2] = true;
          uneed[3] = true;
          uneed[8] = true;
          uneed[9] = true;
          uneed[10] = true;
          uneed[11] = true;
          uneed[13] = true;
          uneed[12] = true;
          uneed[14] = true;
          uneed[15] = true;
          break;
      }
      break;
  }
}


int updateModuleState(gameMove a)
{
  if (((moduleStage <= 3) && (!a.down)) || ((moduleStage > 3) && (a.down)))
  {
    return -1;
  }
  for (int i = 0; i < CHAR_AMT; i++) {
    uneed[i] = false;
  }

  if (a.down)
  {
    solution(uneed);
    validateSolvable();
    if (uneed[a.key]) {
      if (moduleStage == 3) {
        lastTime = global.t;

        Seq = releaseSeq();

      }
      history[moduleStage - 1] = a.key;
      moduleStage++;

      return ACTIVE;
    }
    return FAIL;
  }

  if (moduleStage == 4)
  {
    if (a.key == history[Seq / 100 - 1])
    {

      moduleStage++;

      return 0;
    }
  }
  if (moduleStage == 5)
  {
    if (a.key == history[(Seq / 10) % 10 - 1])
    {
      moduleStage++;
      return 0;
    }
  }
  if (moduleStage == 6)
  {
    if (a.key == history[Seq % 10 - 1])
    {
      Serial.print("you win!!");
      return 1;

    }

  }
  return -1;
}

void validateSolvable() {
  //count amount of valid options
  int unav_cnt = 0, av_cnt = 0;
  for (int i = 0; i < CHAR_AMT; i++)
    if (uneed[i]) {
      av_cnt++;
      for (int j = 0; j < 5; j++)
        if (history[j] == i)
          unav_cnt++;
    }
  if (unav_cnt == av_cnt) {
    for (int i = 0; i < CHAR_AMT; i++)
      uneed[i] = true;
  }
}
