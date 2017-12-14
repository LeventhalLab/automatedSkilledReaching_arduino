#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *actuator = AFMS.getMotor(1);

#define pos A15

float currPos = 0;
float pos1 = 2;

void setup() {
  Serial.begin(9600);
  Serial.println("Please work - This is the start");

  AFMS.begin();

  pinMode(pos, INPUT);

}

void loop() {
  currPos = digitalRead(pos);
  Serial.print("Current Position: ");
  Serial.println(currPos);

  Serial.println(pos1);
  
  if (currPos == pos1) {
    Serial.println("currPos == pos1");
  }
  
  if (currPos<pos1) {
    Serial.println("currPos < pos1");

  }
  if (currPos > pos1) {
    Serial.println("currPos > pos1");

  }

  delay(2000);

}
