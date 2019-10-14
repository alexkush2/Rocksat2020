#include <Stepper.h>
#include <SoftwareSerial.h>              // Needed to include?
#include <Servo.h>
#include <Wire.h>
#include "Time.h"
 #include "DS1307RTC.h"
#include <SPI.h>
#include <SD.h>
#include <stdlib.h>

const int chipSelect = 53; 
int sample = 0;

unsigned long minute_log;              // Minute for the given time t of "now"
unsigned long second_log;              // Second for the given time t of "now"

int input_accelerometer_x  = 3;        // input pin x-axis (accelerometer) 
int input_accelerometer_y  = 2;        // input pin y-axis (accelerometer)
int state_accelerometer_x = 0;         // pin status of x axis accelerometer
int state_accelerometer_y = 0;         // pin status of y axis accelerometer
 
int pulseX, pulseY;                    // variables to read the pulse widths:
int accelerationX, accelerationY;      // variables to contain the resulting accelerations
 
int outPin_to_valve_solenoid = 4;      // define valve_solenoid as digital output pin 4

#define motorSteps 7                   // 360 degrees divided by 1.8 degress
                                       // per revolution of your motor
#define motorPin1 5                    // define motorpin1 as digital output pin 5
#define motorPin2 6                    // define motorpin2 as digital output pin 6
#define motorPin3 7                    // define motorpin3 as digital output pin 7
#define motorPin4 8                    // define motorpin4 as digital output pin 8

int outPin_to_connecting_solenoid = 9; // define connecting_solenoid as digital output pin 9

// initialize of the Stepper library:
Stepper myStepper(motorSteps, motorPin1, motorPin2, motorPin3, motorPin4);
Servo servoLeft;          // Define left servo
Servo servoRight;         // Define right servo

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  // Initialize SD CARD.
  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(53, OUTPUT);
  // see if the card is present and can be initialized:
  
  if (!SD.begin(chipSelect)) { 
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  Wire.begin();
  pinMode(input_accelerometer_x, INPUT);           // declare accelerometer x axis as input
  pinMode(input_accelerometer_y, INPUT);           // declare accelerometer y axis as input 
  pinMode(outPin_to_connecting_solenoid, OUTPUT);  // declare outPin_to_connecting_solenoid outPin as output
  pinMode(outPin_to_valve_solenoid, OUTPUT);       // declare outPin_to_valve_solenoid outPin as output
  myStepper.setSpeed(50);                          // set the motor speed at XX RPMS:
  servoLeft.attach(11);                            // Set left servo to digital pin 11
  servoRight.attach(12);                           // Set right servo to digital pin 9
  retract_stopservo();                             // don't send signal to solenoid retraction servo 
  delay(500);
  locking_forward();                               // move track locking servo forward
  delay(450);   
  locking_stopservo();                             // stop track locking servo after it is in place
  delay(450);

  do
  {
    delay(500);                                   // wait .5ms for sensors to stabilize
    state_accelerometer_x = digitalRead(input_accelerometer_x);  //check x axis of accelerometer
    state_accelerometer_y = digitalRead(input_accelerometer_y);  //check y axis of accelerometer
    // read pulse from x- and y-axes:
    pulseX = pulseIn(input_accelerometer_x,HIGH);  
    pulseY = pulseIn(input_accelerometer_y,HIGH);

    // convert the pulse width into acceleration 
    // accelerationX and accelerationY are in milli-g's: 
    // earth's gravity is 1000 milli-g's, or 1g.
    accelerationX = ((pulseX / 10) - 500) * 8;
    accelerationY = ((pulseY / 10) - 500) * 8;
    // print the acceleration
    //   Serial.print(accelerationX);
    //   print a tab character:
    //   Serial.print("\t");
    //   Serial.print(accelerationY);
    //   Serial.println();
     Serial.println();
     Serial.print(accelerationY); Serial.print("\t"); Serial.print(" acceleration Y");
     Serial.println();
  } while(accelerationY < 500);  //continue checking until movement in y direction
  
 //******************************************************************************************
 //Once accelerometer reads a signal from the x or y axis (aka the rocket has launched,
 //the connecting solenoid connects with first capsule location and the system starts
 //*******************************************************************************************

  take_time_stamp();  // take time stamp to get initial time index
  sample = sample+1;  // increase sample by 1 to start counting samples collected
}


void loop() {
  for (sample = 1; sample < 7; sample++) { //for the ascend - total ascend time is XX.X seconds
    delay(1000);
    digitalWrite(outPin_to_connecting_solenoid, HIGH);// turn ON connecting solenoid
    delay(2000);
    
    if(sample == 1)         // For only sample 1, unlocking locking servo after angular acceleration
    {
      locking_reverse();    // after first cartridge is connected, unlock locking servo
      delay(450);
      locking_stopservo();  // stop track locking servo after it is in place
      delay(450);
    }
    
    open_valve_solenoid();         // turn valve ON to allow air flow
    delay(1000);                   // delay amount of time needed for air flow to fill cartridge
    take_time_stamp();             // take time stamp after valve opens
    close_valve_solenoid();        // turn valve OFF to cut off air flow into cartridge
    delay(1000); 
    retract_connecting_solenoid(); // turn OFF signal to connecting solenoid
    delay(2000);                   // amount solenoid needs to dissipate energy
    retract_forward();             // send signal to servo that retracts solenoid
    delay(300);
    retract_stopservo();           // stop solenoid retraction servo after it is in place
    delay(300);

    myStepper.step(2);             // move stepper motor 7 steps - 12.6 degrees to next cartridge
    myStepper.step(2);
    myStepper.step(2);
    myStepper.step(1);
    delay(1000); 
  }

//******************************************************************************************
//END OF COLLECTING SAMPLES ON THE ASCEND
//*******************************************************************************************

  delay(1000);              
  locking_forward();              // after all 6 samples are taken on ascend, lock track into place with servo
  delay(450);                     // during changes in angular acceleration
  locking_stopservo();            // stop track locking servo after it is in place
  delay(5000);
  
//******************************************************************************************
//START COLLECTING SAMPLES ON THE DESCEND
//*******************************************************************************************
  
  for (sample = 7; sample < 28; sample++) {             //for the descend - total ascend time is XX.X seconds
    delay(1000);
    digitalWrite(outPin_to_connecting_solenoid, HIGH);  // turn ON connecting solenoid
    delay(1000); 
    
    if(sample == 7)                                     // For only sample 7, unlocking locking servo after angular acceleration
    {
      locking_reverse();                                //after 7th cartridge is connected, unlock locking servo
      delay(450);
      locking_stopservo();                              // stop track locking servo after it is in place
      delay(450);
    }
    
    open_valve_solenoid();                              // turn valve ON to allow air flow
    delay(1000);                                        // delay amount of time needed for air flow to fill cartridge
    take_time_stamp();                                  // take time stamp after valve opens
    close_valve_solenoid();                             // turn valve OFF to cut off air flow into cartridge
    delay(1000);
    retract_connecting_solenoid();                      // turn OFF connecting solenoid
    delay(2000);                                        // amount solenoid needs to dissipate energy
    retract_forward();                                  // send signal to servo that retracts solenoid
    delay(300);
    retract_stopservo();                                // stop solenoid retraction servo after it is in place
    delay(300);

    myStepper.step(2);                                  // move stepper motor 7 steps - 12.6 degrees to next cartridge
    myStepper.step(2);
    myStepper.step(2);
    myStepper.step(1);
    delay(1000);
  } 
  while (sample == 28)                                  // after all cartridges are full, delay system in infinite loop
  {
    delay(15000);
  }
}


  //************************\\
 //         FUNCTIONS        \\
//****************************\\

void retract_connecting_solenoid(){ 
  digitalWrite(outPin_to_connecting_solenoid, LOW);    
}

void open_valve_solenoid(){ 
  digitalWrite(outPin_to_valve_solenoid, HIGH);   
}

void close_valve_solenoid(){ 
  digitalWrite(outPin_to_valve_solenoid,LOW);     
}

void locking_forward(){
  servoLeft.write(0);
}

void locking_reverse(){
  servoLeft.write(180);
}

void locking_stopservo(){
  servoLeft.write(90);
}

void retract_forward(){
  servoRight.write(0);
}

void retract_reverse(){
  servoRight.write(180);
}

void retract_stopservo(){
  servoRight.write(90);
}

void take_time_stamp(){
  File dataFile = SD.open("timelog.txt", FILE_WRITE);
   if (dataFile) {  
          // print time stamp to SD
     time_t t = now();   // Store the current time in time variable t 
     minute_log = minute(t);          // Returns the minute for the given time t
     second_log = second(t);          // Returns the second for the given time t 
     dataFile.println(sample);
     dataFile.println(minute_log);
     dataFile.println(second_log);
     dataFile.close();
     Serial.println(); 
     Serial.print("sample number"); Serial.print("\t"); Serial.print(sample);
     // print to the serial port too:
     Serial.println();     
     Serial.print(minute_log); Serial.print("\t"); Serial.print(" time minutes");
     Serial.println();
     Serial.print(second_log); Serial.print("\t"); Serial.print(" time seconds");
     Serial.println();
   }
   // if the file isn't open, pop up an error:
   else {
     Serial.println("error opening datalog.txt");
   }
      //sample++;  
}
