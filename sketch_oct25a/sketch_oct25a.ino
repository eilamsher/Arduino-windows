
int RECV_PIN = 11;


void setup()
{
//  Serial.begin(9600);
//  irrecv.enableIRIn(); // Start the receiver
//  pinMode(LED_BUILTIN, OUTPUT);
pinMode(11, INPUT);
digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  if (digitalRead(11)==LOW) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(3000);
  }
  
  digitalWrite(LED_BUILTIN, LOW);
  delay(3000);
}

