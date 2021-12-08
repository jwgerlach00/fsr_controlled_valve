#include <Arduino.h>
#include <cmath>
#include <ForceModel.h>


// Assign pins
int voltage_probe_pin = A0;

// Force model vars
int force_lower = 50, force_upper = 500;  // grams
int angle_lower = 0, angle_upper = 180;  // degrees
float min_calibration_voltage = 0.01f;  // Corresponding to lowest recorded 500g voltage
float max_calibration_voltage = 3.2f;  // Corresponding to lowest recorded 50g voltage

// Set bit-rate
int analog_res = 12;
int analog_bits = pow(2, analog_res) - 1;


// Instantiate force fit model
ForceModel model(force_lower, force_upper, min_calibration_voltage, max_calibration_voltage);

float pin_to_voltage(int pin) {
    int sensor_value = analogRead(voltage_probe_pin);
    return sensor_value * (3.3f / analog_bits);
}


void setup() {
    Serial.begin(9600);
    analogReadResolution(analog_res);
    analogWriteResolution(analog_res);
    // motor.attach(13);

    // Set pin modes
    pinMode(voltage_probe_pin, INPUT);
}


void loop() {
    float voltage = pin_to_voltage(voltage_probe_pin);
    float grams = model.fit_equation(voltage);

    delay(100);
    Serial.println(grams);
}