#pragma once

#define DEFAULT_SPEED 200
#define DEFAULT_SPEEN_SPEED 80

#include "globals.h"

class MotorController 
{
private:
  const motor *m_Motors = ::motors; // motors[i] where i: 0 - rb, 1 - rf, 2 - lf, 3 - lb
  uint8_t m_BaseSpeed = DEFAULT_SPEED;
  uint8_t m_SpinSpeed = DEFAULT_SPEEN_SPEED;

public:
  MotorController();

  void setup() const;
  
  void resetMotors() const;
  
  void setSpeed(const uint8_t speed);

  void moveAtAngle(const double angle, uint8_t dir = 0) const;

  void spinAroundObj(const int radius = 20) const;

  void MotorController::checkWheels() const;

};

