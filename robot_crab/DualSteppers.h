#pragma once

#define START_POS 0
#define MAX_POS -2000
#define STEPS_PER_REVOLUTION 200
#define DEFAULT_SPEED 200.0

#include <AccelStepper.h>
#include "globals.h"

enum RunResult {
  REACHED_BOUNDARY = 0,
  REACHED_TARGET = 1,
  IN_PROGRESS = 2,
};

class dualSteppers {
private:
  AccelStepper* steppers[2];
  long m_TargetPosition = 0;
  float m_AbsSpeed = DEFAULT_SPEED;

public:
  dualSteppers(AccelStepper& stepper1, AccelStepper& stepper2);

  void reset() const;

  void stop();

  void setSpeed(float new_speed);

  void moveTo(long position);

  RunResult run() const;

  bool runUntilFinished() const;

  float speed() const { return steppers[0]->speed(); }

  long currentPosition() const { return steppers[1]->currentPosition(); }

private:
  bool reachedPosition() const;
};