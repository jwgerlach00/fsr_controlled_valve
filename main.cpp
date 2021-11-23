#include <Arduino.h>
#include <cmath>
#include <servo.cpp>


// Assign pins
int voltage_probe_pin = A0;

// Sampling vars
int sampling_rate = 100;

// Force model vars
int force_lower = 50, force_upper = 500;  // grams
int angle_lower = 0, angle_upper = 180;  // degrees
float min_cal_v = 0.01f;  // Corresponding to lowest recorded 500g voltage
float max_cal_v = 3.2f;  // Corresponding to lowest recorded 50g voltage

// Set bit-rate
int analog_res = 12;
int analog_bits = pow(2, analog_res) - 1;


class ForceModel {
    private:
        int min_force, max_force;
        float min_v, max_v;
    
    public:

        ForceModel(int min_force, int max_force, float min_v, float max_v) {
            this->min_force = min_force;
            this->max_force = max_force;
            this->min_v = min_v;
            this->max_v = max_v;
        }

        float fit_equation(float v) {
            if (v < min_v) {
                return max_force;
            }
            else if (v > max_v) {
                return min_force;
            }
            else {
                return 32.58f*pow(v, 2) - 244.66f*v + 502.76f;
            }
        }
    
};




// Instantiate force fit model
ForceModel model(force_lower, force_upper, min_cal_v, max_cal_v);


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















// void loop() {
//     int long loop_start_time = micros();
  
//     // Get value
//     float voltage = analogRead(voltage_probe_pin);

//     // Plug into model to get force
//     float force = model.fit_equation(voltage);

//     // Map force to servo output between 0 and 180 degrees
//     float servo_angle = map(force, lower_bound, upper_bound, 0, 180);

//     // Move servo to angle
    

//     long int elapsed = micros() - init_time;

//     while (elapsed < 1000000/sampling_rate) {
//         delayMicroseconds(sampling_rate/10);
//         elapsed = micros() - init_time;
//   }

// }

// void setup() {
//   // Start serial monitor
//   Serial.begin(9600);

//   // Set pin modes
//   pinMode(probe, INPUT);
// }

// void loop() {
//   // Read voltage
//   double sensor_value = analogRead(probe);
//   double voltage = sensor_value * (3.3 / 1023);

//   // Slow print-out
//   delay(100);
//   Serial.println(voltage);
// }