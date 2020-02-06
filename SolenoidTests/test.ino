// Testing solenoids
#define SOLENOID_CONTROL 13

// function to test the solenoid
void solenoid_test(int run_count) {
    if (run_count < 0) {
        return;
    }

    while (run_count != 0) {
        digitalWrite(SOLENOID_CONTROL, HIGH);   // turn the solenoid control pin on
        delay(2000);                       
        digitalWrite(SOLENOID_CONTROL, LOW);    // turn the solenoid control pin off
        delay(2000);
        run_count -= 1;
    }
}

void setup() {
    // initialize pin mode for solenoid control
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(SOLENOID_CONTROL, OUTPUT);

    // run the solenoid test
    solenoid_test(3);
}

// loop function to keep arduino alive
void loop() {
//   digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//   delay(20);                       // wait for a second
//   digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
   delay(700);                       // wait for a second
}