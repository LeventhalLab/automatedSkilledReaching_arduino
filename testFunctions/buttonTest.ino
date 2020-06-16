
const int buttPin = 27;
const int ledPin = 43;

int buttState = LOW;

void setup() {
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  
  pinMode(buttPin, INPUT_PULLUP);

  Serial.begin(9600);


}

void loop() {

  buttState = digitalRead(buttPin);
  Serial.println(buttState);

  if (buttState == HIGH) {
    
    digitalWrite(ledPin, HIGH);
    
  } else {
    
    digitalWrite(ledPin, LOW);
    
  }

  delay(50);

}
