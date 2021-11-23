#include <Servo.h>

class ServoUtil {
    private:
        ServoUtil (int pin) {
            Servo.attach(pin);
            // dac 0 in analog WRITE output channels
        }
}