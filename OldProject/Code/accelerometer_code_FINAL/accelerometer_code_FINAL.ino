#include <Wire.h>

int input_accelerometer_x  = 2;    // input pin x-axis (accelerometer)
int input_accelerometer_y  = 3;    // input pin y-axis (accelerometer)
int led = 13;
int state_accelerometer_x = 0;     // pin status of accelerometer
int state_accelerometer_y = 0;     // pin status of accelerometer

int pulseX, pulseY;                // variables to read the pulse widths:
   
int accelerationX, accelerationY;  // variables to contain the resulting accelerations

unsigned long duration; //if digital

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(led, OUTPUT);  // declare LED as output
  pinMode(input_accelerometer_x, INPUT);   // declare accelerometer as input
  pinMode(input_accelerometer_y, INPUT);   // declare accelerometer as input 
  
  do
  {
    //if accelerometer sends an digital signal
    delay(1000);  // wait .5ms for sensors to stabilize
    state_accelerometer_x = digitalRead(input_accelerometer_x);
    state_accelerometer_y = digitalRead(input_accelerometer_y); 

   // read pulse from x- and y-axes:
   pulseX = pulseIn(input_accelerometer_x,HIGH);  
   pulseY = pulseIn(input_accelerometer_y,HIGH);
   
   // convert the pulse width into acceleration
   // accelerationX and accelerationY are in milli-g's: 
   // earth's gravity is 1000 milli-g's, or 1g.
   accelerationX = ((pulseX / 10) - 500) * 8;
   accelerationY = ((pulseY / 10) - 500) * 8;
   
  // print the acceleration
   Serial.print(accelerationX);
   // print a tab character:
   Serial.print("\t");
   Serial.print(accelerationY);
   Serial.println();
   
  } while(accelerationX < 4000 | accelerationY < 1000);
}
  
//Once accelerometer reads a signal from the x or y axis (aka the rocket started to launch, the solenoid connects
//with capsule and the system starts

void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
   delay(1000);               // wait for a second
   digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
   delay(1000);               // wait for a second
     digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
   delay(1000);               // wait for a second
   digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
   delay(1000);               // wait for a second
}
  


