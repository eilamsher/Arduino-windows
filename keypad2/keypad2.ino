#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 4; 
char d1 = '0';
char d2 = '0';
char d3 = '0';
char d4 = '0';
String pass;
String asd;
String Cpass;
int state = 0;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'X', '0', 'Y', 'D'}
};

byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {6,7,8,9}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
  Cpass+='3';
  Cpass+='6';
  Cpass+='9';
  Cpass+='7';
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(10, OUTPUT);
}
  
void loop(){
  char customKey = customKeypad.getKey();
  
  if (customKey){
    if (customKey=='#'){
      if (pass==Cpass){
        open();
        Serial.println('success');
        d1='0';
        d2='0';
        d3='0';
        d4='0';
      }
    }
    else if (customKey=='X'){
      lock();
    }
    else{
      d4=d3;
      d3=d2;
      d2=d1;
      d1=customKey;
    }
    pass=asd;
    pass += d4;
    pass += d3;
    pass += d2;
    pass += d1;
    Serial.println(pass);
  }
}

void lock(){
  if (!state){
    digitalWrite(LED_BUILTIN, HIGH);  
    digitalWrite(10, HIGH);
    state=1;
  }
  
}

void open(){
  if(state){
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(10, LOW);
    state=0;
  }
  
}
