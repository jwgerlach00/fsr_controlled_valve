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
            this->window[array_index] = voltage;
        }
        float average() {
            int voltage_sum = 0;
            for(int i = 0; i < window_size; i++) {
                voltage_sum += window[i];
            }
            return voltage_sum/window_size;
        }
        void replace_oldest(float replacement) {
            this->window[window_pointer] = replacement;
            //
            if(window_pointer < window_size - 1) {
                this->window_pointer += 1;
            }
            else {
                this->window_pointer = 0;
            }
        }
};


#endif