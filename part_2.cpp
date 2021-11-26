#include <Arduino.h>
#include <cmath>
#include <sin_function.cpp>


// Pin assignments
int filter_write_pin = DAC1;
int unfiltered_read_pin = A1;
int filtered_read_pin = A0;

// Configure analog resolution
int analog_res = 12;
int analog_bits = pow(2, analog_res) - 1;

// Set sampling rate
int sampling_rate = 1000;  // Hz, determined through experimentation
int loop_res = 100;

// Math vars
int micro_prefix = 1e6;
int sine_freq = 20;  // Hz

// Instantiate objects
Sinusoid sinusoid;

void setup() {
    // Initiate serial conversion
    Serial.begin(115200);

    // Set read/write resolution
    analogReadResolution(analog_res);
    analogWriteResolution(analog_res);
}

void loop() {
    // Record time beginning loop
    unsigned long loop_start_time = micros();

    // Retreive an output from the sine function
    float sine_volt = sinusoid.run(sine_freq);

    // Cast the output to an integer for pin writing
    int sine_pin_bits = (sine_volt-0.55)*4095/2.2;
    
    // Wait until next sample time
    unsigned long elapsed = micros();
    while (elapsed < (micro_prefix/sampling_rate)) {
        delayMicroseconds(micro_prefix/sampling_rate/loop_res);
        elapsed = micros() - loop_start_time;
    }

    analogWrite(filter_write_pin, sine_pin_bits);
    float volts_filtered = 3.3*analogRead(filtered_read_pin)/analog_bits;
    float volts_unfiltered = 3.3*analogRead(unfiltered_read_pin)/analog_bits;

    // Plot both unfiltered and filtered voltages
    Serial.print(volts_unfiltered);
    Serial.print(",");
    Serial.println(volts_filtered);
}