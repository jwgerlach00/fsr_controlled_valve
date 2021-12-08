#ifndef WINDOW_H
#define WINDOW_H


class Window {
    private:

        float *window;
        int window_size;
        int window_pointer = 0;

    public:

        Window(int window_size) {
            this->window = new float[window_size];
            this->window_size = window_size;
        }

        void populate_array(float voltage, int array_index) {
            /*
                Fills empty array.
            */
            this->window[array_index] = voltage;
        }

        float average() {
            /*
                Averages window.
            */
            float voltage_sum = 0;
            for(int i = 0; i < window_size; i++) {
                voltage_sum += window[i];
            }
            return voltage_sum/float(window_size);
        }

        void replace_oldest(float replacement) {
            /*
                Replaces pointed index in array.
            */
            this->window[window_pointer] = replacement;
            if(window_pointer < window_size - 1) {
                this->window_pointer += 1;
            }
            else {
                this->window_pointer = 0;
            }
        }
};


#endif