#ifndef _MOTORCONTROLLER_H
#define _MOTORCONTROLLER_H

#define DEFAULT_SPEED 200

#include "globals.h"

class MotorController {
private:
  const motor *motors = ::motors; // motors[i] where i: 0 - rb, 1 - rf, 2 - lf, 3 - lb
  const uint8_t defaultSpeed = 200;

public:
  MotorController();

  void setup();
  
  void resetMotors();
  
  void setSpeed(const uint8_t speed);

  void moveAtAngle(const double angle, uint8_t dir = 0);

};

#endif