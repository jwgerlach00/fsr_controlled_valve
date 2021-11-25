#include <Arduino.h>
#include <cmath>


class Sinusoid {
    private:
        float sin_function (unsigned long t, float angular_freq) {
            return sin(angular_freq*t/1000000) + 1.6;
        }
        float convert_freq(float freq) {
            return 2*PI*freq;
        }
    public:
        float run(float freq) {
            // Get current time
            unsigned int t = micros();  // us

            // Convert from Hz to rad/sec
            float w = convert_freq(freq);  // rad/s

            return sin_function(t, w);
        }
};