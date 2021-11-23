#include <Arduino.h>
#include <cmath>


class Sinusoid {
    private:
        int cut_off_freq = 20;  // Hz

        
        float sin_function (unsigned long t, float angular_freq) {
            return 100*sin(angular_freq*t);
        }
        float convert_freq(float freq) {
            return 2*PI*freq; 
        }
    public:
        Sinusoid(int cf) {
            this->cut_off_freq = cf;
        }

        float run_loop(float freq, int time_step) {
            unsigned long init_t = micros();

            unsigned long t = micros();
            float w = convert_freq(freq);
            float out = sin_function(t, w);
            while(t - init_t < time_step) {
                t = micros();
            }
            return out;
        }
};

int cut_off = 20;  // Hz
Sinusoid sinusoid(cut_off);

int time_step = 100;//time step related to sample rate???

void setup() {
    Serial.begin(9600);

}

int freq = 0;  // Starting freq (Hz)
void loop() {
    for(int i = 0; i < 10000; i++) {
        sinusoid.run_loop(freq, time_step);
    }
    freq += 1;
    Serial.println(freq);
}