// threshold of where to turn on the LED
#define GThreshold 25

// input pin
int ZinPin = A0;

// scale of sensor output (+- 200g)
int scale = 200;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);

    // start with LED off
    digitalWrite(LED_BUILTIN, LOW);

}

void loop() {
    // read from pin
    int rawZ = analogRead(ZinPin);

    // scale Z input to range of output, compensating for 5V microcontroller with 3.3v output of sensor
    float scaledZ = map(rawZ, 0, 675, -scale, scale); // 3.3/5 * 1023 =~ 675

    // print calculated G load to terminal
    Serial.println(scaledZ);

    // headless test to try high G readings
    if(scaledZ >= GThreshold){

        // check again for high reading
        rawZ = analogRead(ZinPin);
        scaledZ = map(rawZ, 0, 675, -scale, scale);

        // if still high set LED high
        if(scaledZ >= GThreshold){
            digitalWrite(LED_BUILTIN, HIGH);
        }
    }
}