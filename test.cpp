#include <Arduino.h>
#include <cmath>
#include <Servo.h>
Servo servo;
void setup() {
    Serial.begin(9600);
    servo.attach(2);
    servo.write(45);

}

void loop() {
    servo.write(180);
    Serial.println(180);
    delay(1000);
    servo.write(0);
    Serial.println(0);
    delay(1000);
}