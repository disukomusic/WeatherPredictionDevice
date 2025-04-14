#include <Servo.h>

Servo servo1;

void setup() {
  servo1.attach(9); // Attach servo to pin 9
}

void loop() {
  servo1.write(0);     // Move to 0 degrees
  delay(1000);
  servo1.write(90);    // Move to 90 degrees
  delay(1000);
  servo1.write(180);   // Move to 180 degrees
  delay(1000);
}
