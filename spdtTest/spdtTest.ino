
int switchPin = 35;


void setup() {
  Serial.begin(9600);
  pinMode(switchPin, INPUT_PULLUP);

}

void loop() {
  
  int state = digitalRead(switchPin);

  if (switchPin == 1) {
    Serial.print("state = ");
    Serial.println(state);
  } else {
    Serial.print("state = ");
    Serial.println(state);
  }

delay(2000);

}
