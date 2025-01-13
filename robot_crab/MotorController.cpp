#include "MotorController.h"
#include "utils.h"
#include <math.h>

MotorController::MotorController() 
{
  setSpeed(m_BaseSpeed);
  setup();
  resetMotors();
}

void MotorController::setup() const
{
  for(int i = 0; i < 4; i++)
  {
    pinMode(m_Motors[i].in1, OUTPUT);
    pinMode(m_Motors[i].in2, OUTPUT);
  }
}

void MotorController::resetMotors() const
{
  for(int i = 0; i < 4; i++)
  {
    digitalWrite(m_Motors[i].in1, 0);
    digitalWrite(m_Motors[i].in2, 0);
  }
}

void MotorController::setSpeed(const uint8_t speed) 
{
  for(int i = 0; i < 4; i++)
  {
    analogWrite(m_Motors[i].pwm, speed);
  }
}

void MotorController::moveAtAngle(const double angle, uint8_t dir = 0) const 
{ // dir is 0 - straight, 1 - right, 2 - back, 3 - left.
  double angleRad = (angle / 180) * MATH_PI;

  int16_t motorSpeed[4] = {0}; //the speed going to be inputed into each motor
  motorSpeed[(0 + dir) % 4] = - sin(MATH_PI/4 - angleRad) * m_BaseSpeed;
  motorSpeed[(1 + dir) % 4] =  sin(MATH_PI/4 + angleRad) * m_BaseSpeed;
  motorSpeed[(2 + dir) % 4] =  sin(MATH_PI/4 - angleRad) * m_BaseSpeed;
  motorSpeed[(3 + dir) % 4] = - sin(MATH_PI/4 + angleRad) * m_BaseSpeed;

  // update motors
  for(int i = 0; i < 4; i++)
  {
    analogWrite(m_Motors[i].pwm, abs(motorSpeed[i]));
    bool direction = motorSpeed[i] >= 0;
    digitalWrite(m_Motors[i].in1, direction);
    digitalWrite(m_Motors[i].in2, !direction);
  }
}

void MotorController::spinAroundObj(const int radius = 20) const
{
  // default radius of 20 cms, can be changed.
  int speedDx = 70 - radius;
  int16_t motorSpeed[4] = {0}; //the speed going to be inputed into each motor

  // default move right values (can see further explanation at MotorController::moveAtAngle) plus moment.
  motorSpeed[3] = - (m_SpinSpeed) + speedDx;
  motorSpeed[0] =  (m_SpinSpeed) + speedDx; // if big values i mad ):<
  motorSpeed[1] =  (m_SpinSpeed) + speedDx;
  motorSpeed[2] = - (m_SpinSpeed) + speedDx;

  // update motors
  for(int i = 0; i < 4; i++)
  {
    analogWrite(m_Motors[i].pwm, abs(motorSpeed[i]));
    bool direction = motorSpeed[i] >= 0;
    digitalWrite(m_Motors[i].in1, direction);
    digitalWrite(m_Motors[i].in2, !direction);
  }
}



void MotorController::checkWheels() const 
{
  while(true) 
  {
    for (int i = 0; i < 4; i++) 
    {
      digitalWrite(m_Motors[i].in1, 0);
      digitalWrite(m_Motors[i].in2, 1);
      delay(1000);
      digitalWrite(m_Motors[i].in2, 0);
    }
  }
}