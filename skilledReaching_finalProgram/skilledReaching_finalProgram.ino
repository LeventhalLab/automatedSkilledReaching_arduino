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

#define downButton 50
#define resetButton 48
#define upButton 52

#define onSwitch 45
#define autoSwitch 47

#define led 25 // LED

int motorSpeed = 100;
const int motorSpeed_fast = 200;
const int motorSpeed_slow = 75;

const int reachPos = 0;
const int zeroPos = 900;
const int LEDPos = 200; // Actuator position where the LED should turn on/off for trial indication

const int trialTime = 2000; // How long actuator is in reach position

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
  digitalWrite(led, LOW);

  // For Testing
  Serial.begin(9600);

}

void loop() { 
  while (isOn(digitalRead(onSwitch)) && not isAuto(digitalRead(autoSwitch))) 
  {
    digitalWrite(led, LOW);
    pushButtons();
  } 
  while (isOn(digitalRead(onSwitch)) && isAuto(digitalRead(autoSwitch))) 
  {   
    trial();
    delay(trialTime);
  } 
}

bool isOn(int onSwitchState) 
{ 
  bool value = true;
  while (onSwitchState == LOW) 
  {
    value = false;
    digitalWrite(led, LOW);
    act->setSpeed(0);
    act->run(RELEASE);
    onSwitchState = digitalRead(onSwitch);
  }
  return value;
}

bool isAuto(int autoSwitchState) 
{ 
  if (autoSwitchState == HIGH) 
  {
    return true;
  }
  return false;
}

void retractActuator(int newPos) 
{ 
  int actPos = analogRead(pot);
  while (actPos > newPos) 
  {   
    if (not isOn(digitalRead(onSwitch)))
    {
      break;
    }
    if (actPos <= LEDPos) 
    {
      digitalWrite(led, HIGH);
      motorSpeed = motorSpeed_slow;
    }
    else 
    {
      motorSpeed = motorSpeed_fast;
    }
    act->setSpeed(motorSpeed);
    act->run(BACKWARD);
    actPos = analogRead(pot);
  }
  act->run(RELEASE);
}

void extendActuator(int newPos) 
{    
  int actPos = analogRead(pot);
  while (actPos < newPos) 
  {  
    if (not isOn(digitalRead(onSwitch)))
    {
      break;
    }
    if (actPos >= LEDPos) 
    {
      digitalWrite(led, LOW);
      motorSpeed = motorSpeed_fast;
    }
    else 
    {
      motorSpeed = motorSpeed_slow;
    }
    act->setSpeed(motorSpeed);
    act->run(FORWARD);
    actPos = analogRead(pot);
  }
  act->run(RELEASE);
}

void trial() {
  extendActuator(zeroPos);
  if (not isOn(digitalRead(onSwitch)))
  {
    return;
  }
  delay(50);
  retractActuator(reachPos);
  if (not isOn(digitalRead(onSwitch)))
  {
    return;
  }

}

void pushButtons() {
 
  if (digitalRead(resetButton) == LOW) {
    trial();
  }
  
  while (digitalRead(upButton) == LOW) {
    act->setSpeed(motorSpeed_slow);
    act->run(BACKWARD);

  }
  
  while (digitalRead(downButton) == LOW) {
    act->setSpeed(motorSpeed_slow);
    act->run(FORWARD);
  }
  
  act->setSpeed(0);
  act->run(RELEASE);
}

