int butt1 = 25;

int butt1State = 0;

int butt1CurrCount = 0;
int butt1PastCount = 0;
int butt1Long = 1500;

void setup() {
  pinMode(butt1, INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {
  butt1State = digitalRead(butt1);

  if (butt1State == LOW) {
    butt1CurrCount = millis();
  }

  if (millis() - butt1CurrCount >= butt1Long) {
    Serial.println("Long Press");
  }


}
