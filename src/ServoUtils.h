#include <Servo.h>
#include <Sinusoid.h>

#ifndef SERVOUTILS_H
#define SERVOUTILS_H


class ServoUtils {
    private:
        Servo servo;
        int angle_lower = 0;  // degrees
        int angle_upper = 180;  // degrees
    public:
        ServoUtils(Servo servo, int attach_pin) {
            this->servo = servo;
            this->servo.attach(attach_pin);
        }
        void test_servo(Sinusoid sine, float freq) {
            float sine_val = sine.run(freq);
            int motor_angle = map(sine_val, -sine.mag, sine.mag, 0, 90);
            servo.write(motor_angle);
        }
        void run_servo(int angle) {
            servo.write(angle);
        }
        int grams_to_angle(int grams, int grams_lower, int grams_upper) {
            return map(grams, grams_lower, grams_upper, angle_lower, angle_upper);
        }
};


#endif