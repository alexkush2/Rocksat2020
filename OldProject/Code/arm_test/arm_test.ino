#include <Stepper.h>
#include <Servo.h>
#include <SoftwareSerial.h>              // Needed to include?

//define pins 
int connecting_solenoid = 9; // output pin
int state = 0; // pin status
//initialize servo library
Servo servoLeft;          // Define left servo
Servo servoRight;         // Define right servo

void setup() {
pinMode(connecting_solenoid, OUTPUT); // declare outPin as output
servoRight.attach(12);       // Set right servo to digital pin 9
retract_stopservo();                             // don't send signal to solenoid retraction servo 
delay(500);
}

void loop(){
digitalWrite(connecting_solenoid, HIGH); // turn LED OFF
delay(2000); //amount it holds high
digitalWrite(connecting_solenoid, LOW); // turn Solenoid OFF
delay(2000); //amount needed to dissipate
retract_forward();    // send signal to servo that retracts solenoid
delay(300);
retract_stopservo();  // stop solenoid retraction servo after it is in place
delay(300);
}

void retract_forward(){
  servoRight.write(0);
}

void retract_reverse(){
  servoRight.write(180);
}

void retract_stopservo(){
  servoRight.write(20);
}
