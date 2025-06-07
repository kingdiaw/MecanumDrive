#ifndef MECANUMDRIVE_H
#define MECANUMDRIVE_H

#include <Arduino.h>

class MecanumDrive {
public:
  MecanumDrive(
    float r1, float r2, float r3, float r4,
    int m1Dir, int m1Pwm,
    int m2Dir, int m2Pwm,
    int m3Dir, int m3Pwm,
    int m4Dir, int m4Pwm,
    float scaleFactor = 100.0
  );

  void begin();
  void drive(float vx, float vy, float wz);

private:
  float R1, R2, R3, R4;
  int DIR1, PWM1;
  int DIR2, PWM2;
  int DIR3, PWM3;
  int DIR4, PWM4;
  float K;
  float speedToPwm;

  void setMotor(int dirPin, int pwmPin, float omega);
};

#endif
