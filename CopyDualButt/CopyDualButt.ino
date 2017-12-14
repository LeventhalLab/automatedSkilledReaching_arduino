#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *act = AFMS.getMotor(1);


#define pot A8
#define button 25

const int actErr = 3;

long buttonTimer = 0;
long longPressTime = 250;

boolean buttonActive = false;
boolean longPressActive = false;

void setup() {
  
  AFMS.begin();

  act->setSpeed(150);
  act->run(FORWARD);
  act->run(RELEASE);
  
  pinMode(button, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {

  if (digitalRead(button) == LOW) {

    if (buttonActive == false) {

      buttonActive = true;
      buttonTimer = millis();

    }

    if ((millis() - buttonTimer > longPressTime) && (longPressActive == false)) {

      longPressActive = true;
      Serial.println("Long Press");
      
      while (digitalRead(button) == LOW) {
        act->run(BACKWARD);
      }
      
      act->run(RELEASE);

    } else {

    if (buttonActive == true) {

      if (longPressActive == true) {

        longPressActive = false;

      } else {

        moveAct(500);

      }

      buttonActive = false;

    }

  }
  }

}

void moveAct(int newPos) {
  int actPos = analogRead(pot);
      
  if (actPos < newPos + actErr && actPos > newPos - actErr) {
    act->run(RELEASE);
  }
      
  while (actPos > newPos + actErr) {
    act->run(FORWARD);
    actPos = analogRead(pot);
  }
      
  while (actPos < newPos - actErr) {
    act->run(BACKWARD);
    actPos = analogRead(pot);
  }
  
  act->run(RELEASE);
  
}
