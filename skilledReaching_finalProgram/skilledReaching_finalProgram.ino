/*
 * Skilled Reaching Automated Box
 * 
 * Mouse Single-Pellet Skilled Reaching
 * Final Behavioral Schema (no operant task)
 * 
 * Author: Krista Kernodle
 * Email: kkrista@umich.edu
 *
 * Hardware:
 * ** Arduino/Genuino Mega or Mega 2560
 * ** Adafruit Motor Shield V2
 * ** Actuonix L16-P Micro Linear Actuator
 * ** 3 Buttons
 * ** 2 Switches
 * ** 1 LED
 * 
 * For software flowchart see: 
 * https://app.lucidchart.com/invitations/accept/53b1fb30-76a0-485c-baee-4b8e34677cd4
 */


#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *act = AFMS.getMotor(1); // Actuator is connected to motor terminal 1

#define pot A8 // Potentiometer

#define downButton 52
#define resetButton 48
#define upButton 50

#define onSwitch 45
#define autoSwitch 47

#define led 25 // LED

const int motorSpeed = 50

const int reachPos = 25;
const int zeroPos = 1018;
const int LEDPos = 425; // Actuator position where the LED should turn on/off for trial indication

const int actErr = 5; // Allowable error in potentiometer const int
const int trialTime = 2000; // How long actuator is in reach position
volatile int actPos = 1023; // actuator position; volatile because sometimes pot is off

int softwareSwitchState = 0, autoSwitchState = 0; // States for software and auto switches

void setup() {
    
  // Turn on motor shield
  AFMS.begin();

  // Turn on actuator
  act->setSpeed(motorSpeed);
  act->run(BACKWARD);
  act->run(RELEASE);

  // Define pin modes for all inputs and outputs; _PULLUP -> internal pullup resistor used
  pinMode(pot, INPUT);
  
  pinMode(upButton, INPUT_PULLUP);
  pinMode(resetButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);

  pinMode(onSwitch, INPUT_PULLUP);
  pinMode(autoSwitch, INPUT_PULLUP);
  
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);

}

void loop() {

  digitalWrite(led,LOW);
  
  while isOn(digitalRead(onSwitch)) && not isAuto(digitalRead(autoSwitch) {
    pushButtons();
  }
  
  while isOn(digitalRead(onSwitch)) && isAuto(digitalRead(autoSwitch) {
    trial(True);
    delay(TrialTime);
  }
  
}

void isOn(onSwitchState) {
  while (onSwitchState == LOW) {
    act->setSpeed(0);
    act->run(RELEASE);
    onSwitchState = digitalRead(onSwitch);
  }
  return true
}

void isAuto(autoSwitchState) {
  if (autoSwitchState == HIGH) {
    return true
  }
  return false
}

void retractActuator(int newPos, bool useLED) {
  int actPos = analogRead(pot);
  while (actPos > (newPos + actErr) ) { 
    if not isOn(digitalRead(onSwitch)) {
      break;
    }
    
    if actPos <= LEDpos {
      digitalWrite(LED, HIGH);
    }
    
    act->setSpeed(motorSpeed);
    act->run(BACKWARD);
    actPos = analogRead(pot);

  }

void extendActuator(int newPos) {
  int actPos = analogRead(pot);
  while (actPos < (newPos - actErr)){
    if not isOn(digitalRead(onSwitch)) {
      break;
    }
    
    if actPos >= LEDpos {
      digitalWrite(LED, LOW);
    }
    
    act->setSpeed(motorSpeed);
    act->run(FORWARD);
    actPos = analogRead(pot);
    
  }
}

void trial(bool useLED) {
  extendActuator(zeroPos);
  delay(50);
  retractActuator(reachPos, useLED);
}

void pushButtons() {
  if digitalRead(resetButton) == LOW {
    trial(false);
  }
  
  while digitalRead(upButton) == LOW {
    int actPos = analogRead(pot);
    retractActuator(actPos - 1);
  }
  
  while digitalRead(downButton) == LOW {
    int actPos = analogRead(pot);
    extendActuator(actPos + 1);
  }
}

