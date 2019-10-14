#include <Servo.h> 
 
 Servo myservo_1;  // create servo object to control a servo 
 //Servo myservo_2;

 
void setup() 
{ 
  myservo_1.attach(8);   // attaches the servo on pin 8 to the servo object 
  //myservo_2.attach(9);   // attaches the servo on pin 9 to the servo object
  
}

void loop()
{
    myservo_1.write(90);   // start servo1 at 90 degree position
  //myservo_2.write(90);   // start servo2 at 90 degree position
  
  delay(110);            // delay 11.5 seconds
 // Servo::refresh();

  //myservo_1.write(0);   // start servo1 at 90 degree position
  //delay(110);
  myservo_1.write(179);   // start servo1 at 90 degree position
  //Servo::refresh();
//  myservo_1.write(90);   // start servo1 at 90 degree position
//  //myservo_2.write(90);   // start servo2 at 90 degree position
//  
//  delay(110);            // delay 11.5 seconds
//  myservo_1.write(90);     // Lock track (turn -90 degrees to 0 position)
//  delay(1700);           // delay 17.0 seconds
//  myservo_1.write(180);   // start servo1 at 90 degree position
//  myservo_1.write(90);    // close first valve (turn 90 degrees to 90 position)
 // myservo_1.write(90);     // Lock track (turn -90 degrees to 0 position)
//  myservo_2.write(0);     // open second valve (turn -90 degrees to 0 position)
//  delay(24600);           // delay 24.6 seconds
//  myservo_2.write(90);    // close second valve (turn 90 degrees to 90 position)
//  
//  myservo_3.write(0);     // open third valve (turn -90 degrees to 0 position)
//  delay(35700);           // delay 35.7 seconds
//  myservo_3.write(90);    // close third valve (turn 90 degrees to 90 position)
//  
//  myservo_4.write(0);     // open fourth valve (turn -90 degrees to 0 position)        
//  delay(171300);          // delay 171.3 seconds
//  myservo_4.write(90);    // close fourth valve (turn 90 degrees to 90 position)
//  
//  myservo_3.write(0);     // open third valve (turn -90 degrees to 0 position)          
//  delay(36000);           // delay 36.0 seconds
//  myservo_3.write(90);    // close third valve (turn 90 degrees to 90 position)
//  
//  myservo_2.write(0);     // open second valve (turn -90 degrees to 0 position)   
//  delay(25700);           // delay 25.7 seconds
//  myservo_2.write(90);    // close second valve (turn 90 degrees to 90 position)
//  
//  myservo_1.write(0);     // open first valve (turn -90 degrees to 0 position)   
//  delay(66300);           // delay 66.3 seconds
//  myservo_1.write(90);    // close first valve (turn 90 degrees to 90 position)
} 
 

