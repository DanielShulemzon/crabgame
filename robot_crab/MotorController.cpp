#include "MotorController.h"
#include "utils.h"
#include <math.h>

MotorController::MotorController() {}

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
}

void MotorController::moveAtAngle(const double angle, uint8_t dir = 0) { // dir is 0 - straight, 1 - right, 2 - back, 3 - left.
  double angleRad = angle / (180) * MATH_PI;

  int16_t motorSpeed[4] = {0}; //the speed going to be inputed into each motor
  motorSpeed[(0 + dir) % 4] = - sin(MATH_PI/4 + angle) * DEFAULT_SPEED;
  motorSpeed[(1 + dir) % 4] = - sin(MATH_PI/4 - angle) * DEFAULT_SPEED;
  motorSpeed[(2 + dir) % 4] =  sin(MATH_PI/4 + angle) * DEFAULT_SPEED;
  motorSpeed[(3 + dir) % 4] =  sin(MATH_PI/4 - angle) * DEFAULT_SPEED;

  // update motors
  for(int i = 0; i < 4; i++){
    analogWrite(motors[i].pwm, abs(motorSpeed[i]));
    bool direction = motorSpeed[i] >= 0;
    digitalWrite(motors[i].in1, direction);
    digitalWrite(motors[i].in2, !direction);
  }
}
