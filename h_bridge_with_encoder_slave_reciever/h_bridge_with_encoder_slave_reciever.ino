#include <Encoder.h>
#include <Wire.h>


// 22,968 clicks per revolution
Encoder enc(2, 3);

int incomingByte = 0, inc; // for incoming serial data

//PID constants
double kp = 2;
double ki = 5;
double kd = 1;

unsigned long currentTime, previousTime;
double elapsedTime;
double error;
double lastError;
double input, output, setPoint;
double cumError, rateError;
long Pos  = -999, outputValue;
int power = 0;
int r=5;

void setup() {
  Wire.begin(42);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);
  setPoint = 0;                          //set point at zero degrees
}

void loop() {
  long newPos;

  newPos = enc.read();
  if (newPos != Pos) {
    //Serial.print("encoder = ");
    Serial.println(newPos);
    //Serial.println();
    Pos = newPos;
  }


  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    if (incomingByte > 13) inc = incomingByte - '0';
    // say what you got:
    outputValue = map(inc, 0, 360, 0, 22968);

    /*
      Serial.print("I received: ");
      Serial.println(inc);


      Serial.print("converted to: ");
      Serial.println(outputValue, DEC);
    */
  }

  power = PID();
  digitalWrite(4, power < 0);
  analogWrite(9, abs(power));

  /*
    input = analogRead(A0);                //read from rotary encoder connected to A0
    output = computePID(input);
    delay(100);
    analogWrite(3, output);                //control the motor based on PID value
  */
}

void receiveEvent(int howMany) {
  /*while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
    }*/
  inc = Wire.read();    // receive byte as an integer
  outputValue = map(inc, 0, 360, 0, 22968);

  /*
    Serial.print("received: ");
    Serial.println(inc);         // print the integer
    Serial.print("converted to: ");
    Serial.println(outputValue, DEC);

  */
}

/*
  double computePID(double inp) {
  currentTime = millis();                //get current time
  elapsedTime = (double)(currentTime - previousTime);        //compute time elapsed from previous computation

  error = Setpoint - inp;                                // determine error
  cumError += error * elapsedTime;                // compute integral
  rateError = (error - lastError) / elapsedTime; // compute derivative

  double out = kp * error + ki * cumError + kd * rateError;          //PID output

  lastError = error;                                //remember current error
  previousTime = currentTime;                        //remember current time

  return out;                                        //have function return the PID output
  }*/

int PID() {
  int p = outputValue - Pos;
  if (p > 255)p = 255;
  if (p < -255)p = -255;
  if (abs(p) < r)p = 0;
  return p;
}
