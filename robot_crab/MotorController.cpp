#include "MotorController.h"
#include "utils.h"
#include <math.h>

MotorController::MotorController() {
  setSpeed(baseSpeed);
}

void MotorController::setup() {
  for(int i = 0; i < 4; i++){
    pinMode(motors[i].in1, OUTPUT);
    pinMode(motors[i].in2, OUTPUT);
  }
}

void MotorController::resetMotors() {
  for(int i = 0; i < 4; i++){
    digitalWrite(motors[i].in1, 0);
    digitalWrite(motors[i].in2, 0);
  }
}

void MotorController::setSpeed(const uint8_t speed) {
  for(int i = 0; i < 4; i++){
    analogWrite(motors[i].pwm, speed);
  }
  baseSpeed = speed;
}

void MotorController::moveAtAngle(const double angle, uint8_t dir = 0) { // dir is 0 - straight, 1 - right, 2 - back, 3 - left.
  double angleRad = (angle / 180) * MATH_PI;

  int16_t motorSpeed[4] = {0}; //the speed going to be inputed into each motor
  motorSpeed[(0 + dir) % 4] = - sin(MATH_PI/4 + angleRad) * baseSpeed;
  motorSpeed[(1 + dir) % 4] =  sin(MATH_PI/4 - angleRad) * baseSpeed;
  motorSpeed[(2 + dir) % 4] =  sin(MATH_PI/4 + angleRad) * baseSpeed;
  motorSpeed[(3 + dir) % 4] = - sin(MATH_PI/4 - angleRad) * baseSpeed;

  // update motors
  for(int i = 0; i < 4; i++){
    analogWrite(motors[i].pwm, abs(motorSpeed[i]));
    bool direction = motorSpeed[i] >= 0;
    digitalWrite(motors[i].in1, direction);
    digitalWrite(motors[i].in2, !direction);
  }
}

void MotorController::SpinAroundObj(const double radius = 20) {
  // default radius of 20 cms, can be changed.
  int16_t motorSpeed[4] = {0}; //the speed going to be inputed into each motor

  // default move right values (can see further explanation at MotorController::moveAtAngle) plus moment.
  motorSpeed[3] = - sin(MATH_PI/4) * baseSpeed;
  motorSpeed[0] =  sin(MATH_PI/4) * baseSpeed + radius; // if radius exeedes 55 i mad ):<
  motorSpeed[1] =  sin(MATH_PI/4) * baseSpeed + radius;
  motorSpeed[2] = - sin(MATH_PI/4) * baseSpeed;

  // update motors
  for(int i = 0; i < 4; i++){
    analogWrite(motors[i].pwm, abs(motorSpeed[i]));
    bool direction = motorSpeed[i] >= 0;
    digitalWrite(motors[i].in1, direction);
    digitalWrite(motors[i].in2, !direction);
  }
}
