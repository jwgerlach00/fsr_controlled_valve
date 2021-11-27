#include <Arduino.h>
#include <Servo.h>
#include <TimedLoop.h>
#include <Sinusoid.h>
#include <ServoUtils.h>

// Set pins
int servo_pin = 3;

// Instantiate objects
TimedLoop timed_loop;
Sinusoid sine;
Servo servo;
ServoUtils servo_utils(servo, servo_pin);



// Set math variables
float freq = 0.5f;  // Hz
int angle = 0;

// Set sampling and resolution variables
int sampling_rate = 1000;
int loop_resolution = 20;
int sine_resolution = 1000;

void setup() {
    Serial.begin(115200);

    // Enhance sinusoid resolution for mapping
    sine.mag = sine_resolution;
}

void loop() {
    unsigned long loop_start_time = micros();
    servo_utils.test_servo(sine, freq);
    timed_loop.micro_wait(loop_start_time, sampling_rate, loop_resolution);
}

