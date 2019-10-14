
/*
 Stepper Motor Controller
 language: Wiring/Arduino

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8, 9, 10 and 11 of the Arduino.

 The motor moves 200 steps in one direction.

 Created 2 Feb. 2013

 */

// define the pins that the motor is attached to. You can use
// any digital I/O pins.

#include <Stepper.h>
#include <SoftwareSerial.h> 	           // Needed to include 

#define motorSteps 8 // 360 degrees divided by 1.8 degress
                           // per revolution of your motor
#define motorPin1 5
#define motorPin2 6
#define motorPin3 7
#define motorPin4 8
//#define ledPin 13

// initialize of the Stepper library:
Stepper myStepper(motorSteps, motorPin1, motorPin2, motorPin3, motorPin4); 

void setup() {
  // set the motor speed at 60 RPMS:
  myStepper.setSpeed(50);  
 // Initialize the Serial port (pulses per second):
 //Serial.begin(9600);         
}

void loop() {
  // Step forward 200 steps:
 // Serial.println("Clockwise");
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(2);
  myStepper.step(1);
  delay(3000); //wait 0.5 ms

}

