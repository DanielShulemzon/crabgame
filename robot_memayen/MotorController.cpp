#include "MotorController.h"
#include "utils.h"

MotorController::MotorController() {}

void MotorController::setup(){
  for(int i = 0; i < 4; i++){
    pinMode(motors[i].in1, OUTPUT);
    pinMode(motors[i].in2, OUTPUT);
  }
}

void MotorController::resetMotors(){
  for(int i = 0; i < 4; i++){
    digitalWrite(motors[i].in1, 0);
    digitalWrite(motors[i].in2, 0);
  }
}

void MotorController::setSpeed(const uint8_t speed){
  for(int i = 0; i < 4; i++){
    analogWrite(motors[i].pwm, speed);
  }
}
