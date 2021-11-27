#include <Arduino.h>
#include <cmath>
#ifndef SINUSOID_H
#define SINUSOID_H


class Sinusoid {
    private:

        float sin_function (unsigned long t, float angular_freq, int prefix) {
            /*
                Returns a sine function with public sine features.
            */
            return mag*sin(angular_freq*t/prefix) + offset;
        }

        float hertz_to_rads(float freq) {
            /*
                Converts Hertzian frequency to radian frequency.
            */
            return 2*PI*freq;
        }

    public:

        // Sine features
        int mag = 1;
        float offset = 1.6;

        float run(float freq, int prefix) {
            /*
                Runs all private functions in order.
            */

            // Get current time
            unsigned int t = micros();  // us

            // Convert frequency
            float w = hertz_to_rads(freq);  // rad/s

            return sin_function(t, w, prefix);
        }
};


#endif