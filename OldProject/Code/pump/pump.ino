#include <Stepper.h>
#include <SoftwareSerial.h>              // Needed to include?


int pump = 8; // output pin

int state = 0; // pin status


void setup() {
pinMode(pump, OUTPUT); // declare outPin as output
}
void loop(){
digitalWrite(pump, HIGH); // turn LED OFF
delay(2000); //amount it holds high
digitalWrite(pump, LOW); // turn Solenoid OFF
delay(2000); //amount needed to dissipate
}


