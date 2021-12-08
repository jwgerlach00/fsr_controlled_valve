#include <cmath>
#include <Arduino.h>
#include <ForceModel.h>
#include <ServoUtils.h>
#include <Window.h>
#include <TimedLoop.h>


// Pin assignments
int filtered_read_pin = A0;
int servo_write_pin = 2;

// Configure analog resolution
int analog_resolution = 12;
int analog_bits = pow(2, analog_resolution) - 1;

// Math vars
int micro_prefix = 1e6;
int milli_prefix = 1e3;

// Set sampling rate and window size
int window_time_length = 200;  // Milliseconds to wait between samples
int sampling_rate = 100;  // Hz
int loop_resolution = 100;  // Steps for wait loop
int window_size = (window_time_length/milli_prefix)*sampling_rate;

// Force model vars
int force_lower = 50, force_upper = 500;  // grams
int angle_lower = 0, angle_upper = 180;  // degrees
float min_calibration_voltage = 0.01f;  // Corresponding to lowest recorded 500g voltage
float max_calibration_voltage = 3.2f;  // Corresponding to lowest recorded 50g voltage

// Instantiate objects
ForceModel force_model(force_lower, force_upper, min_calibration_voltage, max_calibration_voltage);
Servo servo;
ServoUtils servo_utils(servo, servo_write_pin);
Window window(window_size);
TimedLoop timed_loop;

// Initialize additional vars
int grams;
int angle;

void setup() {
    // Initiate serial conversion
    Serial.begin(115200);

    // Set read/write resolution
    analogReadResolution(analog_resolution);
    analogWriteResolution(analog_resolution);
}

// Main loop variables
unsigned long times_through_loop = 0;  // Total times through loop during entire run-time
unsigned long loop_start_time;
float average_voltage;
float current_voltage;

void loop() {
    loop_start_time = micros();

    // Read voltage from filter output
    current_voltage = 3.3*analogRead(filtered_read_pin)/analog_bits;

    if(times_through_loop < unsigned(window_size)) {
        // Fill array
        window.populate_array(current_voltage, times_through_loop);
    }
    else {
        // Replace oldest value in array
        window.replace_oldest(current_voltage);

        // Average window voltages
        average_voltage = window.average();

        // Convert voltage to angle
        grams = force_model.fit_equation(average_voltage);
        grams = int(grams);
        angle = servo_utils.grams_to_angle(grams, force_lower, force_upper);
        Serial.println(angle);

        servo_utils.run_servo(angle);
    }
    times_through_loop += 1;

    // Wait loop
    timed_loop.micro_wait(loop_start_time, sampling_rate, loop_resolution);
}