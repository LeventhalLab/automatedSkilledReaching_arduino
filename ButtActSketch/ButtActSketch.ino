
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *act = AFMS.getMotor(1);

#define pot A8

#define butt1 25
#define butt2 27
#define butt3 29

long butt1Timer = 0;
long longButt1Time = 1000;

boolean butt1Active = false;
boolean longButt1Active = false;

int actPos = 0;
const int actErr = 3;

void setup() {
  AFMS.begin();

  act->setSpeed(150);
  act->run(FORWARD);
  act->run(RELEASE);

  pinMode(butt1, INPUT_PULLUP);
  pinMode(butt2, INPUT_PULLUP);
  pinMode(butt3, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {

  if (digitalRead(butt1) == HIGH) {
    // Button Pressed
    
    if (butt1Active == false) {
      butt1Active = true;
      butt1Timer = millis();
    }

    if ((millis() - butt1Timer > longButt1Time) && (longButt1Active == false)) {
      longButt1Active = true;
      Serial.println("First serial line");
    }

  } else {
    // Button Not Pressed

    if (butt1Active == true) {
      butt1Active = false;
    }

    if (longButt1Active == true) {
      longButt1Active = false;
    } else {
      Serial.println("Second serial line");
    }

    butt1Active = false;
    delay(50);
    
  }

  
 /* 
  butt1State = digitalRead(butt1);
  Serial.println(butt1State);
  while (butt1State == LOW) {
    act->run(BACKWARD);
    butt1State = digitalRead(butt1);
  }
  act->run(RELEASE);

  
  butt2State = digitalRead(butt2);
  Serial.println(butt2State);
  if (butt2State == LOW) {
    act->run(RELEASE);
    butt2State = digitalRead(butt2);
  }
  
  
  butt3State = digitalRead(butt3);
  Serial.println(butt3State);
  while (butt3State == LOW) {
    act->run(FORWARD);
    butt3State = digitalRead(butt3);
  }
  act->run(RELEASE);
 */

}

void moveAct(int newPos) {
  actPos = analogRead(pot);
      
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
