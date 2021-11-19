#include <Arduino.h>

int probe = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(probe, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  double sensor_value = analogRead(probe);
  double voltage = sensor_value * (3.3 / 1023);
  delay(100);
  Serial.println(voltage);

}