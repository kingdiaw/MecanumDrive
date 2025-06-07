#include "MecanumDrive.h"

MecanumDrive::MecanumDrive(
  float r1, float r2, float r3, float r4,
  int m1Dir, int m1Pwm,
  int m2Dir, int m2Pwm,
  int m3Dir, int m3Pwm,
  int m4Dir, int m4Pwm,
  float scaleFactor
) : R1(r1), R2(r2), R3(r3), R4(r4),
    DIR1(m1Dir), PWM1(m1Pwm),
    DIR2(m2Dir), PWM2(m2Pwm),
    DIR3(m3Dir), PWM3(m3Pwm),
    DIR4(m4Dir), PWM4(m4Pwm),
    speedToPwm(scaleFactor)
{
  K = 0.0675 + 0.0625;
}

void MecanumDrive::begin() {
  pinMode(DIR1, OUTPUT); pinMode(PWM1, OUTPUT);
  pinMode(DIR2, OUTPUT); pinMode(PWM2, OUTPUT);
  pinMode(DIR3, OUTPUT); pinMode(PWM3, OUTPUT);
  pinMode(DIR4, OUTPUT); pinMode(PWM4, OUTPUT);
}

void MecanumDrive::setMotor(int dirPin, int pwmPin, float omega) {
  bool direction = (omega >= 0);
  int pwm = min(abs(omega * speedToPwm), 255);
  digitalWrite(dirPin, direction);
  analogWrite(pwmPin, pwm);
}

void MecanumDrive::drive(float vx, float vy, float wz) {
  float omega1 = (1.0 / R1) * (vx - vy - wz * K);
  float omega2 = (1.0 / R2) * (vx + vy + wz * K);
  float omega3 = (1.0 / R3) * (vx + vy - wz * K);
  float omega4 = (1.0 / R4) * (vx - vy + wz * K);

  setMotor(DIR1, PWM1, omega1);
  setMotor(DIR2, PWM2, omega2);
  setMotor(DIR3, PWM3, omega3);
  setMotor(DIR4, PWM4, omega4);
}
