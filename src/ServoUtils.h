#include <Servo.h>
#include <Sinusoid.h>

#ifndef SERVOUTILS_H
#define SERVOUTILS_H


class ServoUtils {
    public:
        void test_servo(Servo servo, Sinusoid sine, float freq) {
            float sine_val = sine.run(freq);
            int motor_angle = map(sine_val, 0, sine.mag, 0, 90);
            servo.write(motor_angle);
        }
};


#endif