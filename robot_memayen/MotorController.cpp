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

void MotorController::moveAtAngle(const double angle) {
  double speedRatio = 1 - (abs(angle) / 90); //for example:  angle = 30 deg will give ratio of 0.66 between the 2 sides

  int16_t motorSpeed[4] = {defaultSpeed, defaultSpeed, -defaultSpeed, -defaultSpeed};
  if(angle < 0){
    motorSpeed[0] *= speedRatio;
    motorSpeed[1] *= speedRatio;
  }
  else{
    motorSpeed[2] *= speedRatio;
    motorSpeed[3] *= speedRatio;
  }

  // update motor speed
  for(int i = 0; i < 4; i++){
    analogWrite(motors[i].pwm, abs(motorSpeed[i]));
  }

  // activate motors
  for(int i = 0; i < 4; i++){
    digitalWrite(motors[i].in1, motorSpeed[i] >= 0);
    digitalWrite(motors[i].in2, motorSpeed[i] < 0); // the opposite of the first pin, they both return a boolean where true = 1, false = 0.
  }
}
