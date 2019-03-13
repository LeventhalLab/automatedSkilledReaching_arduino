
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *act = AFMS.getMotor(1);

#define pot A8

#define butt1 52
#define butt2 51
#define butt3 49

long butt2Timer = 350;
long longButt2Time = 1000;

boolean butt2Active = false;
boolean longButt2Active = false;

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

  if (digitalRead(butt2) == HIGH) {
    // Button Pressed
    
    if (butt2Active == false) {
      butt2Active = true;
      butt2Timer = millis();
    }

    if ((millis() - butt2Timer > longButt2Time) && (longButt2Active == false)) {
      longButt2Active = true;
      Serial.println("First serial line");
    }

  } else {
    // Button Not Pressed

    if (butt2Active == true) {
      butt2Active = false;
    }

    if (longButt2Active == true) {
      longButt2Active = false;
    } else {
      Serial.println("Second serial line");
    }

    butt2Active = false;
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
