#ifndef _MOTORCONTROLLER_H
#define _MOTORCONTROLLER_H

#include "globals.h"

class MotorController {
private:
  const motor *motors = ::motors; // motors[i] where i: 0 - rb, 1 - rf, 2 - lf, 3 - lb
  static const uint8_t defaultSpeed = 150;

public:
  
  MotorController();

  void setup();
  
  void resetMotors();
  
  void setSpeed(const uint8_t speed);

  void moveAtAngle(const double angle);

};

#endif