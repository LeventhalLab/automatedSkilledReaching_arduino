  /* 
    Skilled Reaching Automated Box - No Operant Task (no IR beam)
  */

// Include packages required for motor shield

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Name motor shield and "motor" - actuator

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *act = AFMS.getMotor(1); // Actuator is connected to motor terminal 1

// Define Pins

#define pot A8 // Potentiometer

#define butt1 52 // Buttons 1-3
#define butt2 48
#define butt3 50

#define softwareSwitch 45 // This switch will turn "on/off" the software
#define autoSwitch 47 // This switch will turn the actuator controls to "auto" vs "manual"

#define led 25 // LED

// Define constant variables

// Actuator positions
const int zeroPos = 1010; 
const int startPos = 900; 
const int readyPos = 500;
const int reachPos = 35;

const int actErr = 10; // Error in potentiometerconst int
const int trialTime = 2000; // How long actuator is in fully extended position
const int intTrialInt = 100; // How long actuator remains in fully retracted position before moving to ready position

// Define variables that change

volatile int actPos = 0; // actuator position; volatile because sometimes pot is off

int softwareSwitchState = 0, autoSwitchState = 0; // States for software and auto switches

long buttonTimer = 0; // Used to differentiate long button and short button pushes
long buttonTime = 350; // Time required for a long button push (ms)

// Boolean variables for differentiating long and short button pushes
boolean buttonActive = false;
boolean longPressActive = false;

boolean butt1Active = false;
boolean butt2Active = false;
boolean butt3Active = false;

boolean actStop = false;

void setup() {
  
  // Turn on motor shield
  AFMS.begin();

  // Turn on actuator
  act->setSpeed(150);
  act->run(BACKWARD);
  act->run(RELEASE);

  // Define pin modes for all inputs and outputs; _PULLUP -> internal pullup resistor used
  pinMode(pot, INPUT);
  
  pinMode(butt1, INPUT_PULLUP);
  pinMode(butt2, INPUT_PULLUP);
  pinMode(butt3, INPUT_PULLUP);

  pinMode(softwareSwitch, INPUT_PULLUP);
  pinMode(autoSwitch, INPUT_PULLUP);

  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);

}

void loop() {

  // Turn LED off
  digitalWrite(led,LOW); 
  
  // Read state of softwareSwitch
  softwareSwitchState = digitalRead(softwareSwitch);
  

  // If the softwareSwitch is in the "Off" position
  if (softwareSwitchState == LOW) {
      // Other switch (autoSwitch) not used
      // Buttons not used
      // LED turned off (this is the original state of the LED)
      
      // Actuator stops moving
      act->setSpeed(0);
      act->run(RELEASE);
      pushButtons();
  }


  // If the softwareSwitch is in the "On" position 
  if (softwareSwitchState == HIGH) {
 
    // Read state of autoSwitch
    autoSwitchState = digitalRead(autoSwitch);

    // If autoSwitch is in "Manual" position
    if (autoSwitchState == LOW) {
      // LED not used
      
      pushButtons(); // Monitor buttons for long and short pushes to control actuator
      
    }

    // If autoSwitch is in "Auto" position
    if (autoSwitchState == HIGH) {
      // Actuator control dependent on IR beam break & timing (Is there a sensor I should use? IR?)
      // Buttons can override auto control and force re-entry to the auto loop
      // LED turns on when actuator reaches "readyPos"
      // Actuator remains at "reachPos" for "trialTime"
      // LED turns off when actoator reaches "readyPos"
      // Actuator remains at "zeroPos" for "intTrialInt"

      pushButtons(); // Monitor buttons to control actuator if something isn't working correctly

      moveAct(readyPos);

      digitalWrite(led, HIGH);

      moveAct(reachPos);

      delay(trialTime);

      moveAct(readyPos);

      digitalWrite(led, LOW);

      moveAct(zeroPos);

      delay(intTrialInt);
  
    }
    
  }

  // Delay to prevent bouncing
  delay(50);
  
}

void moveAct(int newPos) {
  // This function moves the actuator to a specified potentiometer position
  // INPUT: newPos - a number between 0 and 1023 that the actuator should be positioned at

  // Read potentiometer
  int actPos = analogRead(pot);

  // Set Motor Speed to 150
  act->setSpeed(150);

  // If the actuator is above or below newPos (accounting for error)
  if (actPos > newPos + actErr || actPos < newPos - actErr) {

    // When actuator is above newPos
    while (actPos > newPos + actErr) {

      // Move actuator "Forward"
      act->setSpeed(150);
      act->run(BACKWARD);
      
      // Update actPos
      actPos = analogRead(pot);
      Serial.println(actPos);
      
      // Monitor buttons (mostly for emergency stop)
      pushButtons();
      
      // If the "emergency stop" is hit, break the while loop; note that I'm not sure why this particular while/if loop seems to work as it does
      while ((butt2Active == true) && (longPressActive == false)) {
        if (digitalRead(butt2) == LOW) {
          break;
        }
      }
    }

    // When actuator is below newPos
    while (actPos < newPos - actErr) {

      // Move actuator "Backward"
      act->run(FORWARD);

      // Update actPos
      actPos = analogRead(pot);

      // Monitor buttons (mostly for emergency stop)
      pushButtons();

      // If the "emergency stop" is hit, break the while loop; note that I'm not sure why this particular while/if loop seems to work as it does
      while ((butt2Active == true) && (longPressActive == false)) {
        if (digitalRead(butt2) == LOW) {
          break;
        }
      }
      
    }
  }

  // Stop the actuator from moving
  act->run(RELEASE);
  
}

void pushButtons() {
  // This function is used to control long vs short pushes of the button
  // Long pushes are triggered on the press
  // Short pushes are triggered on the release

  // Read state of buttons (only one button can be active at a time):
  if (digitalRead(butt1) == LOW) {
    
    if (buttonActive == false) {
      buttonActive = true;
      buttonTimer = millis();
    }

    butt1Active = true;

  } else if (digitalRead(butt2) == LOW) {

    if (buttonActive == false) {
      buttonActive = true;
      buttonTimer = millis();
    }

    butt2Active = true;

  } else if (digitalRead(butt3) == LOW) {

    if (buttonActive == false) {
      buttonActive = true;
      buttonTimer = millis();
    }

    butt3Active = true;

  }

  // If there is a long push on any button
  if ((buttonActive == true) && (millis() - buttonTimer > buttonTime) && (longPressActive == false)) {

    longPressActive = true;

    // Define what to do for each button's long push
    if (butt1Active == true) {

      while(digitalRead(butt1) == LOW) {
        
        act->setSpeed(150);
        act->run(BACKWARD);
        actPos = analogRead(pot);
        Serial.println(actPos);
      }
      
    } else if (butt2Active == true) {

      moveAct(readyPos);
    
    } else if(butt3Active == true) {
      
      while(digitalRead(butt3) == LOW) {
        act->setSpeed(150);
        act->run(FORWARD);
        actPos = analogRead(pot);
        Serial.println(actPos);
      }
      

    }

    // Stop actuator from moving
    act->run(RELEASE);
  }

  // If there is a short button press
  if ((buttonActive == true) && (digitalRead(butt1) == HIGH) && (digitalRead(butt2) == HIGH) && digitalRead(butt3) == HIGH) {

    // If there was a long press before this (i.e., you just released the long button press)
    if (longPressActive == true) {
      longPressActive = false;

    } else {

      // Define what to do for short button press
      if (butt1Active == true) {
        moveAct(reachPos);     
      } else if (butt2Active == true) {
        act->setSpeed(0);
        act->run(RELEASE);

      } else if (butt3Active == true) {
        moveAct(startPos);
      }

    }

    // Reset all boolean variables to false
    buttonActive = false;
    butt1Active = false;
    butt2Active = false;
    butt3Active = false;

  }
  
}

