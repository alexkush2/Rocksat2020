/*Example sketch to control a stepper motor with A4988/DRV8825 stepper motor driver and Arduino without a library. More info: https://www.makerguides.com */

// Define stepper motor connections and steps per revolution:
#define dirPin 2
#define stepPin 3
#define stepsPerRevolution 200

void setup() {
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop() {
  // Set the spinning direction clockwise:
  digitalWrite(dirPin, HIGH);

  // Spin the stepper motor 1 revolution slowly:
  for (int i = 0; i < 10; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(5000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(5000);
  }

  delay(2000);
}

// /*Example sketch to control a stepper motor with DRV8825 stepper motor driver, AccelStepper library and Arduino: acceleration and deceleration. More info: https://www.makerguides.com */

// // Include the AccelStepper library:
// #include <AccelStepper.h>

// // Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
// #define dirPin 2
// #define stepPin 3
// #define motorInterfaceType 1

// // Create a new instance of the AccelStepper class:
// AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

// int i = 0;

// void setup() {
//   // Set the maximum speed and acceleration:
//   stepper.setMaxSpeed(100);
//   stepper.setAcceleration(30);
// }

// void loop() {
//   i += 10;
//   // Set the target position:
//   stepper.moveTo(i);
//   // Run to target position with set speed and acceleration/deceleration:
//   stepper.runToPosition();

//   delay(1000);
// }