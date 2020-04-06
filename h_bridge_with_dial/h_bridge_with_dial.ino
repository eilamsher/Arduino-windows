byte pinA = 3;  // Connected to CLK on KY-040
byte pinB = 4;  // Connected to DT on KY-040

int encoderPosCount = 0;
int pinALast;
int aVal;

int PWM = 0;
byte diff = 20;

void setup() {
  // put your setup code here, to run once:
  pinMode (pinA, INPUT);
  pinMode (pinB, INPUT);
  pinALast = digitalRead(pinA);
  Serial.begin (9600);

}

void loop() {
  // put your main code here, to run repeatedly:


  digitalWrite(2, PWM > 0);
  analogWrite(9, abs(PWM));



  aVal = digitalRead(pinA);
  if (aVal != pinALast) { // Means the knob is rotating
    // if the knob is rotating, we need to determine direction
    // We do that by reading pin B.
    if (digitalRead(pinB) != aVal) {  // Means pin A Changed first - We're Rotating Clockwise
      encoderPosCount ++;
      PWM = PWM + diff;

    } else {// Otherwise B changed first and we're moving CCW
      encoderPosCount--;
      PWM = PWM - diff;

    }
    if (PWM > 255) PWM = 255;
    if (PWM < -255) PWM = -255;
    Serial.print ("Rotated: ");
    Serial.print("Encoder Position: ");
    Serial.println(encoderPosCount);
    Serial.print("PWM: ");
    Serial.println(PWM);
  }
  pinALast = aVal;



}
