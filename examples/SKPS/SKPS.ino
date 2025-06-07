//#include <SoftwareSerial.h>
#include <MecanumDrive.h>
#include <Servo.h>

//const byte rxPin = 2;
//const byte txPin = 8;

//======= CREATE OBJECT FROM CLASS =======
//// 1) Set up a new SoftwareSerial object
//SoftwareSerial mySerial(rxPin, txPin);

// 2) Set up a new Servo object
Servo Left;
Servo Right;
Servo Gripper;

// 3) Set up a nre MecanumDrive object
MecanumDrive robot(
  0.03, 0.03, 0.03, 0.03,  // R1 to R4
  A0, 3,                   // M1(DIR,PWM)
  A1, 6,                   // M2
  A2, 5,                   // M3
  A3, 11                   // M4
);

//============== SKPS PROTOCOL ==============
#define p_select 0
#define p_joyl 1
#define p_joyr 2
#define p_start 3
#define p_up 4
#define p_right 5
#define p_down 6
#define p_left 7
#define p_l2 8
#define p_r2 9
#define p_l1 10
#define p_r1 11
#define p_triangle 12
#define p_circle 13
#define p_cross 14
#define p_square 15
#define p_joy_lx 16
#define p_joy_ly 17
#define p_joy_rx 18
#define p_joy_ry 19
#define p_joy_lu 20
#define p_joy_ld 21
#define p_joy_ll 22
#define p_joy_lr 23
#define p_joy_ru 24
#define p_joy_rd 25
#define p_joy_rl 26
#define p_joy_rr 27

#define p_con_status 28
#define p_motor1 29
#define p_motor2 30

//========ARM/GRIPPER LIMIT===============
#define UPPER_LIMIT 120
#define LOWER_LIMIT 0
#define CLOSE_LIMIT 100
#define OPEN_LIMIT  30
//========MECANUM SPEED LIMIT=============
#define VX_MAX  0.02
#define VY_MAX  0.03
#define WZ_MAX  0.2
//=========OFFSET MECANUM=================
#define FORWARD_OFFSET  0.011
#define BACKWARD_OFFSET -0.01
//========================================
//Global Variable
long t0, t1_servo;
int digital_button, button_old;
int rawX, rawY;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //mySerial.begin(9600);
  robot.begin();

  Left.attach(4);
  Right.attach(7);
  Gripper.attach(12);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (skps(p_up) == 0) {
    robot.drive(VX_MAX, 0.0, FORWARD_OFFSET);   // FORWARD
  } else if (skps(p_right) == 0) {
    robot.drive(0.0, -VY_MAX, 0.0);             // RIGHT (strafe)
  } else if (skps(p_down) == 0) {
    robot.drive(-VX_MAX, 0.0, BACKWARD_OFFSET);  // BACKWARD
  } else if (skps(p_left) == 0) {
    robot.drive(0.0, VY_MAX, 0.0);               // LEFT (strafe)
  } else if (skps(p_l2) == 0) {
    robot.drive(0.0, 0.0, WZ_MAX);               // PIVOT COUNTER-CLOCKWISE
  } else if (skps(p_r2) == 0) {
    robot.drive(0.0, 0.0, -WZ_MAX);              // PIVOT CLOCKWISE
  } else {
    robot.drive(0.0, 0.0, 0.0);                 //STOP
  }
  
  if (millis() > t1_servo) {
    static int16_t pos1;
    static int16_t pos2;
    t1_servo = millis() + 15;
    if (skps(p_triangle) == 0) {
      if (++pos1 > UPPER_LIMIT) pos1 = UPPER_LIMIT;
    }
    else if (skps(p_cross) == 0) {
      if (--pos1 < LOWER_LIMIT) pos1 = LOWER_LIMIT;
    }
    if(skps(p_circle)==0){    //gripper close
      if(++pos2 > CLOSE_LIMIT)  pos2 = CLOSE_LIMIT;
    }
    else if(skps(p_square) == 0){ //open
      if(--pos2 < OPEN_LIMIT) pos2 = OPEN_LIMIT;
    }
    Left.write(pos1);
    Right.write(abs(175-pos1));
    Gripper.write(pos2);
  }
}

// skps function
//=======================================================================
unsigned char skps(unsigned char data)  //function to read button and joystick
{                                       //information on ps controller
  Serial.write(data);
  while (Serial.available() == 0);
  return Serial.read();
}

void skps_vibrate(unsigned char motor, unsigned char value) {  //function to control the vibrator motor
  Serial.write(motor);
  Serial.write(value);
}
