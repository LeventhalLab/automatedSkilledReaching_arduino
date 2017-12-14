/*
 * Button Interrupt Sketch
 */

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *act = AFMS.getMotor(1);

#define pot A8

#define butt1 18
#define butt2 19

#define ledPin 43

volatile int butt1State = 0, butt2State = 0;

volatile int actPos = 0;

void setup() {
  
  AFMS.begin();

  act->setSpeed(150);
  act->run(FORWARD);
  act->run(RELEASE);

  pinMode(butt1, INPUT);
  pinMode(butt2, INPUT);

  attachInterrupt(5, butt1_ISR, HIGH);
  attachInterrupt(4, butt2_ISR, HIGH);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  Serial.begin(9600);

}

void loop() {
  actPos = analogRead(pot);
  Serial.println(actPos);

}

void butt1_ISR() {
  digitalWrite(ledPin, HIGH);
  while (actPos < 1000) {
  act->run(FORWARD);
  actPos = analogRead(pot);
  }
}

void butt2_ISR() {
  while (actPos > 1000) {
  act->run(BACKWARD);
  actPos = analogRead(pot);
  }
}

