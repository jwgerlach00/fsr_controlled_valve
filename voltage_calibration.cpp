#include <Arduino.h>


// Pin assignments
int probe = A0;

void setup() {
  // Start serial monitor
  Serial.begin(9600);

  // Set pin modes
  pinMode(probe, INPUT);
}

void loop() {
  // Read voltage
  int sensor_value = analogRead(probe);
  float voltage = sensor_value * (3.3 / 1023);

  // Slow print-out
  delay(100);
  Serial.println(voltage);
}