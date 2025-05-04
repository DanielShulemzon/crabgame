#include "MotorController.h"
#include "utils.h"
#include <math.h>

MotorController::MotorController() {
  setup();
  setSpeed(m_BaseSpeed);
  resetMotors();
}

void MotorController::setup() const {
  for (int i = 0; i < 4; i++) {
    pinMode(m_Motors[i].in1, OUTPUT);
    pinMode(m_Motors[i].in2, OUTPUT);
  }
}

void MotorController::resetMotors() const {
  for (int i = 0; i < 4; i++) {
    digitalWrite(m_Motors[i].in1, 0);
    digitalWrite(m_Motors[i].in2, 0);
  }
}

void MotorController::setSpeed(uint8_t speed) {
  m_BaseSpeed = speed;
  for (int i = 0; i < 4; i++) {
    analogWrite(m_Motors[i].pwm, speed);
  }
}

void MotorController::moveAtAngle(double angle, uint8_t dir = 0) const {  // dir is 0 - straight, 1 - right, 2 - back, 3 - left.
  double angleRad = (angle / 180) * PI;

  // strengthen weak motors
  int16_t helpSpeed = m_BaseSpeed * 1.1;

  int16_t motorSpeed[4] = { 0 };  //the speed going to be inputed into each motor
  motorSpeed[(0 + dir) % 4] = -sin(PI / 4 - angleRad) * m_BaseSpeed;
  motorSpeed[(1 + dir) % 4] = sin(PI / 4 + angleRad) * helpSpeed;
  motorSpeed[(2 + dir) % 4] = sin(PI / 4 - angleRad) * helpSpeed;
  motorSpeed[(3 + dir) % 4] = -sin(PI / 4 + angleRad) * m_BaseSpeed;

  // update motors
  for (int i = 0; i < 4; i++) {
    analogWrite(m_Motors[i].pwm, abs(motorSpeed[i]));
    bool direction = motorSpeed[i] >= 0;
    digitalWrite(m_Motors[i].in1, direction);
    digitalWrite(m_Motors[i].in2, !direction);
  }
}

void MotorController::spinAroundObj(uint8_t radius = 20) const {
  int speedDx = 15;
  int16_t motorSpeed[4] = { 0 };  //the speed going to be inputed into each motor

  // strengthen weak motors
  int16_t helpSpeed = m_SlowSpeed * 1.1;

  // default move right values (can see further explanation at MhotorController::moveAtAngle) plus moment.
  motorSpeed[3] = -(m_SlowSpeed) + speedDx;
  motorSpeed[0] = (helpSpeed) + speedDx;
  motorSpeed[1] = (helpSpeed) + speedDx;
  motorSpeed[2] = -(m_SlowSpeed) + speedDx;

  // update motors
  for (int i = 0; i < 4; i++) {
    analogWrite(m_Motors[i].pwm, abs(motorSpeed[i]));
    bool direction = motorSpeed[i] >= 0;
    digitalWrite(m_Motors[i].in1, direction);
    digitalWrite(m_Motors[i].in2, !direction);
  }
}


void MotorController::spinInPlace(bool clockwise = false, uint8_t speed = DEFAULT_SLOW_SPEED) const {
  // set all motors spinning in the same direction
  for (int i = 0; i < 4; i++) {
    analogWrite(m_Motors[i].pwm, speed);
    digitalWrite(m_Motors[i].in1, 1 - clockwise);
    digitalWrite(m_Motors[i].in2, clockwise);
  }
}

void MotorController::checkWheels() const {
  while (true) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(m_Motors[i].in1, 0);
      digitalWrite(m_Motors[i].in2, 1);
      delay(1000);
      digitalWrite(m_Motors[i].in2, 0);
    }
  }
}