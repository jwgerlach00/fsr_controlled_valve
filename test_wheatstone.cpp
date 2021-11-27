#include <Arduino.h>


// Pin assignments
int v_plus_probe = A0;
int v_minus_probe = A1;

void setup() {
  // Initiate serial conversation
  Serial.begin(9600);

  // Set pin modes
  pinMode(v_plus_probe, INPUT);
  pinMode(v_minus_probe, INPUT);
}

void loop() {
  // Read pin values
  int v_plus_pin_val = analogRead(v_plus_probe);
  int v_minus_pin_val = analogRead(v_minus_probe);

  float wheatstone_v_out = (v_plus_pin_val - v_minus_pin_val) * (3.3 / 1023);

  // Slow print-out
  delay(100);
  Serial.println(wheatstone_v_out);
}