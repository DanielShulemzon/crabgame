#include "LeadScrewStepper.h"
#include "utils.h"


LeadScrewStepper::LeadScrewStepper(const stepperLS& leftStepper, const stepperLS& rightStepper,
                                    uint8_t leftServoPin, uint8_t rightServoPin) :
      m_RightStepper(AccelStepper::DRIVER, leftStepper.step, leftStepper.dir),
     m_LeftStepper(AccelStepper::DRIVER, rightStepper.step, rightStepper.dir) {

  m_LeftStepper.setCurrentPosition(START_POS);
  m_LeftStepper.setMaxSpeed(1000);
  m_LeftStepper.setSpeed(m_Rps);
  m_LeftStepper.setAcceleration(100);

  m_RightStepper.setCurrentPosition(START_POS);
  m_RightStepper.setMaxSpeed(1000);
  m_RightStepper.setSpeed(m_Rps);
  m_RightStepper.setAcceleration(100);

  m_LeftServo.attach(leftServoPin);
  m_RightServo.attach(rightServoPin);

  m_LeftServo.write(LEFT_SERVO_START);
  m_RightServo.write(RIGHT_SERVO_START);
  delay(1000);
}

void LeadScrewStepper::reset() const 
{
    // Start moving both motors to the starting position without blocking
    m_LeftStepper.moveTo(START_POS);
    m_RightStepper.moveTo(START_POS);

    // fizzbeen, win.
    while (m_RightStepper.isRunning() || m_LeftStepper.isRunning()) 
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
  long currentSteps = m_RightStepper.currentPosition(); // they are totally parallel.
  if(currentSteps < MAX_POS || currentSteps > START_POS)
  {
    //PANIC
    reset();
    return false;
  }
  return true;
}

bool LeadScrewStepper::runSpeedToPositionAndCheck() const 
{
  // if out of boundries, return false.
  m_LeftStepper.runSpeedToPosition();
  m_RightStepper.runSpeedToPosition();
  long currentSteps = m_RightStepper.currentPosition(); // they are totally parallel.
  if(currentSteps < MAX_POS || currentSteps > START_POS)
  {
    //PANIC
    reset();
    return false;
  }
  return true;
}

bool LeadScrewStepper::runUntilFinished() const {
  while(m_LeftStepper.distanceToGo() != 0 && m_RightStepper.distanceToGo() != 0) {
    if(!runAndCheck()) {
      serialPrintf("You stupid n-\n");
      return false;
    }
  }
  return true;
}

bool LeadScrewStepper::moveTo(const long pos) const {
  m_LeftStepper.moveTo(pos);
  m_RightStepper.moveTo(pos);
}

void LeadScrewStepper::pickUpObj() const {
  m_LeftStepper.move(STEPS_PER_REVOLUTION / 8);
  m_RightStepper.move(STEPS_PER_REVOLUTION / 8);
  for(int pos = 90; pos >= 45; pos--) {
    m_LeftServo.write(R2L_CONVERT(pos));
    m_RightServo.write(pos);
    if(!runAndCheck()) {
      serialPrintf("You stupid n-\n");
    }
    delay(10);
  }
  runUntilFinished();
}

void LeadScrewStepper::putDownObj() const {
  m_LeftStepper.move(-(STEPS_PER_REVOLUTION / 8));
  m_RightStepper.move(-(STEPS_PER_REVOLUTION / 8));
  for(int pos = 45; pos <= 90; pos++) {
    m_LeftServo.write(R2L_CONVERT(pos));
    m_RightServo.write(pos);
    if(!runAndCheck()) {
      serialPrintf("You stupid n-\n");
    }
    delay(10);
  }
  runUntilFinished();
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

void LeadScrewStepper::checkServos() const
{ 
  while (true)
  { 
    for(int pos = 90; pos >= 45; pos--) {
      m_LeftServo.write(R2L_CONVERT(pos));
      m_RightServo.write(pos);
      delay(10);
    }

    delay(1000);

    for(int pos = 45; pos <= 90; pos++) {
      m_LeftServo.write(R2L_CONVERT(pos));
      m_RightServo.write(pos);
      delay(10);
    }

    delay(1000);
  }
}

void LeadScrewStepper::checkObjHandle() const {
  moveTo(-1000);
  runUntilFinished();
  delay(1000);
  pickUpObj();
  delay(1000);
  putDownObj();
}