const int shouldExplode = 2;
const int isSolved = 3;

const int sw1 = 5;
const int sw2 = 6;
const int sw3 = 9;
const int sw4 = 10;
const int pb1 = 11;
const int led1 = 12;
const int led2 = 13;
//const int led3 = 18;

int state[18];
int temp;

void setup() {
  // put your setup code here, to run once:
pinMode(sw1, INPUT);
pinMode(sw2, INPUT);
pinMode(sw3, INPUT);
pinMode(sw4, INPUT);
pinMode(pb1, INPUT);

pinMode(led1, OUTPUT);
digitalWrite(led1, LOW); 
pinMode(led2, OUTPUT);
digitalWrite(led2, LOW); 
//pinMode(led3, OUTPUT);
//digitalWrite(led13, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
if(digitalRead(sw1) == HIGH){
  digitalWrite(led1, HIGH); 
  digitalWrite(led2, LOW); 
}
  else{
  digitalWrite(led1, LOW); 
  digitalWrite(led2, HIGH); 
}
}


void buildArray()
{
  state[0] = getState();
if(get1()&&!get3()&&get4() {
  
}
elseif(get1()&&!get3()) {

}
    
}

void stage1() {


}






int getState()
{
  temp = 0;
  if(digitalRead(sw1) == HIGH)
    temp = 1;
    if(digitalRead(sw2) == HIGH)
    temp = temp + 10;
     if(digitalRead(sw3) == HIGH)
    temp = temp + 100;
     if(digitalRead(sw4) == HIGH)
    temp = temp + 1000;

    return temp;
}
int get4(int line)
{
  return(state[line]%10;
}
int get3(int line)
{
  return((state[line]/10)%10;
}
int get2(int line)
{
  return(((state[line]/10)/10)%10;
}
int get1(int prev)
{
  return((((state[line]/10)/10)/10)%10;
}
