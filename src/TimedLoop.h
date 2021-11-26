#include <Arduino.h>
#include <cmath>

#ifndef TIMEDLOOP_H
#define TIMEDLOOP_H


class TimedLoop {
    private:
        int micro_prefix = 1e6;
    public:
        void micro_wait(unsigned long loop_start_time, int sampling_rate, int loop_resolution) {
            // Initialize elapsed time
            unsigned long elapsed = micros();

            while (elapsed < (micro_prefix/sampling_rate)) {
                delayMicroseconds(micro_prefix/sampling_rate/loop_resolution);
                elapsed = micros() - loop_start_time;
            }
        }
};


#endif