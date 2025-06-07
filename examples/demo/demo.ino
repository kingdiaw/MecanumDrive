#include <MecanumDrive.h>

MecanumDrive robot(
  0.03, 0.03, 0.03, 0.03, // R1 to R4
  4, 3,   // M1
  7, 6,   // M2
  10, 9,  // M3
  12, 11  // M4
);

void setup() {
  robot.begin();
}

void loop() {
  float vx = 0.2;
  float vy = 0.0;
  float wz = 0.5;

  robot.drive(vx, vy, wz);
  delay(100);
}
