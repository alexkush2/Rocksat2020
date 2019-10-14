#include "Time.h"
#include <Wire.h>
#include "DS1307RTC.h"
#include <SPI.h>
#include <SD.h>
#include <stdlib.h>

const int chipSelect = 10;   // Arduino Ethernet shield: pin 4
                             // Adafruit SD shields and modules: pin 10
                             // 53 ON THE MEGA!!!!
unsigned long minute_log;   // Minute for the given time t of "now"
unsigned long second_log;   // Second for the given time t of "now"
//unsigned long t;
//#define TIME_MSG_LEN  11   // time sync to PC is HEADER followed by unix time_t as ten ascii digits
//#define TIME_HEADER  'T'   // Header tag for serial time sync message
//#define TIME_REQUEST  7    

                            
void setup()
{
   // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  // Initialize SD CARD.
  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);        //*******53 ON THE MEGA!!!!!
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

void loop()
{
    delay(5000);
   File dataFile = SD.open("timelog.txt", FILE_WRITE);
   if (dataFile) {  
          // print time stamp to SD
     time_t t = now();   // Store the current time in time variable t 
     minute_log = minute(t);          // Returns the minute for the given time t
     second_log = second(t);          // Returns the second for the given time t 
     dataFile.println(minute_log);
     dataFile.println(second_log);
     dataFile.close();
     
     // print to the serial port too:
     Serial.println(minute_log);
     Serial.println(" time minutes");
     Serial.println(" ");
     Serial.println(second_log);
     Serial.println(" time seconds");
     Serial.println(" ");
   }
   // if the file isn't open, pop up an error:
   else {
     Serial.println("error opening datalog.txt");
   }
}





