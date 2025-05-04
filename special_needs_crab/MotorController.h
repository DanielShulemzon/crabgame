#pragma once

#define DEFAULT_SPEED 60
#define DEFAULT_SLOW_SPEED 40

#include "globals.h"

class MotorController 
{
private:
  const Motor *m_Motors = ::motors; // motors[i] where i: 0 - lb, 1 - rb, 2 - rf, 3 - lf
  uint8_t m_BaseSpeed = DEFAULT_SPEED;
  uint8_t m_SlowSpeed = DEFAULT_SLOW_SPEED;

public:
  MotorController();

  void setup() const;
  
  void resetMotors() const;
  
  void setSpeed(uint8_t speed);

  void moveAtAngle(double angle, uint8_t dir = 0) const;

  void spinAroundObj(uint8_t radius = 20) const;

  void spinInPlace(bool clockwise = false, uint8_t speed = DEFAULT_SLOW_SPEED) const;

  void checkWheels() const;

};

