#include "LeadScrewStepper.h"


LeadScrewStepper::LeadScrewStepper(uint8_t stepPin, uint8_t dirPin, uint8_t serPin)
    : m_Stepper(AccelStepper::DRIVER, stepPin, dirPin) {
  m_Stepper.setCurrentPosition(0);
  m_Stepper.setMaxSpeed(8192);
  m_Stepper.setSpeed(m_Rps);
  m_Stepper.setAcceleration(1000);

  m_Servo.attach(serPin);
}

void LeadScrewStepper::reset() const 
{
  m_Stepper.runToNewPosition(0);
}

bool LeadScrewStepper::runAndCheck() const 
{
  // if out of boundries, return false.
  m_Stepper.run();
  long currentSteps = m_Stepper.currentPosition();
  if(currentSteps >= MAX_STEPS || currentSteps <= MIN_STEPS)
  {
    //PANIC
    reset();
    return false;
  }
  return true;
}


void LeadScrewStepper::checkBoundries() const
{
  while(true) {
    m_Stepper.runToNewPosition(MAX_STEPS);
    delay(1000);
    m_Stepper.runToNewPosition(MIN_STEPS);
    delay(1000);
  }
}

void LeadScrewStepper::servoChecker() const
{ 
  while (true)
  { 
    m_Servo.write(0);
    delay(1000);
    m_Servo.write(45);
    delay(1000);
  }
}