#include "DualSteppers.h"

dualSteppers::dualSteppers(AccelStepper& stepper1, AccelStepper& stepper2)
{
  stepper1.setMaxSpeed(1000);
  stepper2.setMaxSpeed(1000);

  steppers[0] = &stepper1;
  steppers[1] = &stepper2;
}

void dualSteppers::reset() const
{
  moveTo(START_POS);
  runUntilFinished();
}

void dualSteppers::setSpeed(float new_speed)
{
  m_AbsSpeed = new_speed;
}

void dualSteppers::moveTo(long new_position)
{
  m_TargetPosition = new_position;

  if (currentPosition() < new_position)
  {
    steppers[0]->setSpeed(m_AbsSpeed);
    steppers[1]->setSpeed(m_AbsSpeed);
  } else {
    steppers[0]->setSpeed(-m_AbsSpeed);
    steppers[1]->setSpeed(-m_AbsSpeed);
  }
}

RunResult dualSteppers::run() const 
{
  if (currentPosition() < MAX_POS || currentPosition() > START_POS)
  {
    reset();
    return REACHED_BOUNDARY;
  } else if (!reachedPosition()) {
    steppers[0]->runSpeed();
    steppers[1]->runSpeed();
    Serial.println(currentPosition());
  } else {
    return REACHED_TARGET;
  }
  return IN_PROGRESS;
}

bool dualSteppers::runUntilFinished() const
{
  while (run() == IN_PROGRESS)
    // Serial.println(currentPosition())
    ;
}

bool dualSteppers::reachedPosition() const
{
  long pos = currentPosition();
  float cur_speed = speed();

  // Moving forward: stop when position >= target
  // Moving backward: stop when position <= target
  return (cur_speed > 0 && pos >= m_TargetPosition) || (cur_speed < 0 && pos <= m_TargetPosition);
}