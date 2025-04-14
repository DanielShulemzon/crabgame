#include "DualSteppers.h"

DualSteppers::DualSteppers(AccelStepper& stepper1, AccelStepper& stepper2)
{
  stepper1.setMaxSpeed(1000);
  stepper2.setMaxSpeed(1000);

  steppers[0] = &stepper1;
  steppers[1] = &stepper2;
}

void DualSteppers::reset() const
{
  moveTo(START_POS);
  runUntilFinished();
}

void DualSteppers::stop()
{
  m_TargetPosition = currentPosition();
}

void DualSteppers::setSpeed(float new_speed)
{
  m_AbsSpeed = new_speed;
}

void DualSteppers::moveTo(long new_position)
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

RunResult DualSteppers::run() const 
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

bool DualSteppers::runUntilFinished() const
{
  while (run() == IN_PROGRESS)
    // Serial.println(currentPosition())
    ;
}

bool DualSteppers::reachedPosition() const
{
  long pos = currentPosition();
  float cur_speed = speed();

  // Moving forward: stop when position >= target
  // Moving backward: stop when position <= target
  return (cur_speed > 0 && pos >= m_TargetPosition) || (cur_speed < 0 && pos <= m_TargetPosition);
}