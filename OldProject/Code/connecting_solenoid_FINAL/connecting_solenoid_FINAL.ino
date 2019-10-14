#include <Stepper.h>
#include <SoftwareSerial.h>              // Needed to include?


int connecting_solenoid = 8; // output pin

int state = 0; // pin status


void setup() {
pinMode(connecting_solenoid, OUTPUT); // declare outPin as output
//digitalWrite(connecting_solenoid, HIGH); // turn LED OFF
//delay(10000); //amount it holds high
//digitalWrite(connecting_solenoid, LOW); // turn Solenoid OFF
//delay(10000); //amount needed to dissipate

}

void loop(){
digitalWrite(connecting_solenoid, HIGH); // turn LED OFF
delay(2000); //amount it holds high
digitalWrite(connecting_solenoid, LOW); // turn Solenoid OFF
delay(2000); //amount needed to dissipate
}


