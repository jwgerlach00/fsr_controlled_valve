#include <Servo.h>
#include <Sinusoid.h>
#ifndef SERVOUTILS_H
#define SERVOUTILS_H


class ServoUtils {
    private:

        int angle_lower = 0;  // degrees
        int angle_upper = 180;  // degrees
        int micro_prefix = 1e6;

        Servo servo;

    public:

        ServoUtils(Servo servo, int attach_pin) {
            this->servo = servo;
            this->servo.attach(attach_pin);
        }

        void test_servo(Sinusoid sine, float freq) {
            /*
                Tests servo movement for Stage II.
                Maps a sine wave to a 0-90 degree angle range.
            */
            float sine_val = sine.run(freq, micro_prefix);
            int motor_angle = map(sine_val, -sine.mag + sine.offset, sine.mag + sine.offset, 0, 90);
            servo.write(motor_angle);
        }

        void run_servo(int angle) {
            /*
                Writes angle to servo object.
            */
            servo.write(angle);
        }

        int grams_to_angle(int grams, int grams_lower, int grams_upper) {
            /*
                Maps a grams range to an angle range.
            */
            return map(grams, grams_lower, grams_upper, angle_lower, angle_upper);
        }
};


#endif