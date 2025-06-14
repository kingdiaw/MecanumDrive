# MecanumDrive

An Arduino library to control a 4-wheeled Mecanum robot using inverse kinematics. This library supports precise velocity-based control using individual wheel radii and allows direct GPIO pin assignment for each motor.

## Features

- Implements full inverse kinematics for Mecanum drive.
- Individual wheel radius support for calibration.
- Simple API with `drive(vx, vy, wz)` function.
- Works with basic H-bridge drivers (e.g., L298N) using digital pins.

## Hardware Configuration

Top View:
```
 M1          M2
 |            |
 M3          M4
```
Each motor is connected to two digital output pins for direction control (PWM support optional depending on driver implementation).

## Inverse Kinematics

The library uses the following equations to compute angular velocities for each wheel:
```
ω1 = (vx - vy - ωz(L + W)) / R1 // front left (M1)
ω2 = (vx + vy + ωz(L + W)) / R2 // front right (M2)
ω3 = (vx + vy - ωz(L + W)) / R3 // back left (M3)
ω4 = (vx - vy + ωz(L + W)) / R4 // back right (M4)
```

Where:

- `R1`, `R2`, `R3`, `R4`: individual wheel radii (in meters)
- `L`: distance from robot center to front/back wheels (meters)
- `W`: distance from robot center to left/right wheels (meters)
- `vx`: linear velocity in X direction (forward/backward), in m/s
- `vy`: linear velocity in Y direction (sideways), in m/s
- `wz`: angular velocity around Z axis (rotation), in rad/s

---

## Quick Start

### Example Code

```cpp
#include <MecanumDrive.h>

MecanumDrive robot(
  0.03, 0.03, 0.03, 0.03, // R1 to R4 (wheel radii in meters)
  4, 3,   // M1: Top Left
  7, 6,   // M2: Top Right
  10, 9,  // M3: Bottom Left
  12, 11  // M4: Bottom Right
);

void setup() {
  robot.begin();
}

void loop() {
  float vx = 0.2;  // forward velocity (m/s)
  float vy = 0.0;  // no strafing
  float wz = 0.5;  // rotate counter-clockwise (rad/s)

  robot.drive(vx, vy, wz);
  delay(100);
}
```
### Constructor
```cpp
MecanumDrive robot(
  R1, R2, R3, R4,    // wheel radii
  m1_pin1, m1_pin2,  // motor 1 (top-left)
  m2_pin1, m2_pin2,  // motor 2 (top-right)
  m3_pin1, m3_pin2,  // motor 3 (bottom-left)
  m4_pin1, m4_pin2   // motor 4 (bottom-right)
);
```
### Begin Method
```cpp
robot.begin();
```
Initializes motor control pins as outputs.

### Drive Method
```cpp
robot.drive(vx, vy, wz);
```

Drives the robot with specified velocities.

- vx: forward/backward speed
- vy: strafe speed (left/right)
- wz: angular velocity (rotation)

### Requirements
Arduino board (Uno, Nano, Mega, etc.)
Four DC motors with H-bridge drivers (e.g., L298N)
Compatible with standard Arduino digital pins

### License
MIT License – see LICENSE

### Author
kingdiaw
GitHub: @kingdiaw
