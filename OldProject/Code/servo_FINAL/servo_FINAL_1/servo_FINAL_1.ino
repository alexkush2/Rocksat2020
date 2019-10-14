#include <Servo.h>

Servo servoLeft;          // Define left servo
Servo servoRight;         // Define right servo

void setup() { 
  servoLeft.attach(8);  // Set left servo to digital pin 10
  servoRight.attach(9);  // Set right servo to digital pin 9
} 

void loop() {            // Loop through motion tests
  forward();             // Example: move forward
  delay(450);   // Wait 2000 milliseconds (2 seconds)
  stopRobot();
  delay(5000);
  reverse();
  delay(450);
  stopRobot();
  delay(5000);  //delay forward
 // turnRight();
  //_1_stopRobot();
  //delay(500);
  //turnLeft();
  //delay(500);
  //stopRobot();
  //delay(10000);
}

// Motion routines for forward, reverse, turns, and stop
void forward() {
  servoLeft.write(0);
  servoRight.write(180);
}

void reverse() {
  servoLeft.write(180);
  servoRight.write(0);
}

void turnRight() {
  servoLeft.write(180);
  servoRight.write(180);
}
void turnLeft() {
  servoLeft.write(0);
  servoRight.write(0);
}

void stopRobot() {
  servoLeft.write(90);
  servoRight.write(90);
}
