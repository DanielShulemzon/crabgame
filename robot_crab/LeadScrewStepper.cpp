#include "LeadScrewStepper.h"


LeadScrewStepper::LeadScrewStepper(uint8_t dirPin1, uint8_t stepPin1, uint8_t dirPin2,
                     uint8_t stepPin2, uint8_t serPin1, uint8_t serPin2) :
      m_LeftStepper(AccelStepper::DRIVER, stepPin1, dirPin1),
     m_RightStepper(AccelStepper::DRIVER, stepPin2, dirPin2) {
  m_LeftStepper.setCurrentPosition(START_POS);
  m_LeftStepper.setMaxSpeed(1000);
  m_LeftStepper.setSpeed(m_Rps);
  m_LeftStepper.setAcceleration(100);

  m_RightStepper.setCurrentPosition(START_POS);
  m_RightStepper.setMaxSpeed(1000);
  m_RightStepper.setSpeed(m_Rps);
  m_RightStepper.setAcceleration(100);

  m_LeftServo.attach(serPin1);
  m_RightServo.attach(serPin2);
}

void LeadScrewStepper::reset() const 
{
    // Start moving both motors to the starting position without blocking
    m_LeftStepper.moveTo(START_POS);
    m_RightStepper.moveTo(START_POS);

    // fizzbeen, win.
    while (m_LeftStepper.isRunning() || m_RightStepper.isRunning()) 
    {
        // Update both motors
        m_LeftStepper.run();
        m_RightStepper.run();

        // Small delay so motors won't combust.
        delay(10);
    }

    // Both motors are now at position 0. Very Nice!
}

bool LeadScrewStepper::runAndCheck() const 
{
  // if out of boundries, return false.
  m_LeftStepper.run();
  m_RightStepper.run();
  long currentSteps = m_LeftStepper.currentPosition(); // they are totally parallel.
  if(currentSteps >= MAX_POS || currentSteps <= START_POS)
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
    m_LeftStepper.runToNewPosition(MAX_POS);
    delay(1000);
    m_LeftStepper.runToNewPosition(START_POS);
    delay(1000);
    m_RightStepper.runToNewPosition(MAX_POS);
    delay(1000);
    m_RightStepper.runToNewPosition(START_POS);
    delay(1000);
  }
}

void LeadScrewStepper::servoChecker() const
{ 
  while (true)
  { 
    m_LeftServo.write(0);
    m_RightServo.write(0);
    delay(1000);
    m_LeftServo.write(45);
    m_RightServo.write(45);
    delay(1000);
  }
}