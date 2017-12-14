
#define ledPin 41
#define SENSORPIN 49

int sensorState = 0, lastState = 0;

void setup() {
  
  pinMode(ledPin, OUTPUT);

  pinMode(SENSORPIN, INPUT);
  digitalWrite(SENSORPIN, HIGH);

  Serial.begin(9600);

}

void loop() {

  sensorState = digitalRead(SENSORPIN);

  if (sensorState == LOW) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }

  if (sensorState && !lastState) {
    Serial.println("Unbroken");
  }
  if (!sensorState && lastState) {
    Serial.println("Broken");
  }
  
  lastState = sensorState;

}
