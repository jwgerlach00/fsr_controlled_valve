#include <Arduino.h>
#include <cmath>

#ifndef SINUSOID_H
#define SINUSOID_H


class Sinusoid {
    private:
        float sin_function (unsigned long t, float angular_freq) {
            return mag*sin(angular_freq*t/1000000) + 1.6;
        }
        float convert_freq(float freq) {
            return 2*PI*freq;
        }
    public:
        int mag = 1;

        float run(float freq) {
            // Get current time
            unsigned int t = micros();  // us

            // Convert from Hz to rad/sec
            float w = convert_freq(freq);  // rad/s

            return sin_function(t, w);
        }
};


#endif