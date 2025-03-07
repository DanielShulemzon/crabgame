#include "LeadScrewStepper.h"
#include "utils.h"


LeadScrewStepper::LeadScrewStepper(const stepperLS& leftStepper, const stepperLS& rightStepper,
                                    uint8_t leftServoPin, uint8_t rightServoPin) :
      m_LeftStepper(AccelStepper::DRIVER, leftStepper.step, leftStepper.dir),
      m_RightStepper(AccelStepper::DRIVER, rightStepper.step, rightStepper.dir),
      m_Steppers() {

  m_LeftStepper.setCurrentPosition(START_POS);
  m_LeftStepper.setSpeed(m_Rps);

  m_RightStepper.setCurrentPosition(START_POS);
  m_RightStepper.setSpeed(m_Rps);

  m_Steppers.addStepper(m_LeftStepper);
  m_Steppers.addStepper(m_RightStepper);

  m_LeftServo.attach(leftServoPin);
  m_RightServo.attach(rightServoPin);

  m_LeftServo.write(LEFT_SERVO_START);
  m_RightServo.write(RIGHT_SERVO_START);
  delay(1000);

}

void LeadScrewStepper::reset() const 
{
  // Start moving both motors to the starting position without blocking
  m_Steppers.moveTo(start_pos);
  m_Steppers.runSpeedToPosition();
  // Both motors are now at position 0. Very Nice!
}

bool LeadScrewStepper::check() const 
{
  // if out of boundries, return false.
  m_Steppers.run();
  long right = m_RightStepper.currentPosition();
  long left = m_LeftStepper.currentPosition();
  if(right < MAX_POS || right > START_POS || left < MAX_POS || left > START_POS)
  {
    //PANIC
    reset();
    return false;
  }
  return true;
}

bool LeadScrewStepper::closeOnObj() const
{
  int read;
  m_Steppers.moveTo(max_pos);
  while (m_Steppers.run())
  {
    read = Utils::getFsrNewton();
    // Utils::serialPrintf("1: %d 2: %d, also 2 moves to: %d\n", m_LeftStepper.currentPosition(), m_RightStepper.currentPosition(), m_LeftStepper.targetPosition());
    if (!check() || read >= 10) break;
  }
  return read >= 10;
}

void LeadScrewStepper::pickUpObj() const
{
  long new_positions[2] = {m_LeftStepper.currentPosition() - (STEPS_PER_REVOLUTION / 8),
                              m_RightStepper.currentPosition() - (STEPS_PER_REVOLUTION / 8)};
  m_Steppers.moveTo(new_positions);
  
  unsigned long prevTime = millis();
  int pos = 90;

  while (pos > 45)  // Continue until pos reaches 45
  {
    if (millis() - prevTime >= 10)  // Update servos every 10 ms
    {
      prevTime = millis(); // Reset timer

      m_LeftServo.write(R2L_CONVERT(pos));
      m_RightServo.write(pos);
      pos--;
    }

    m_Steppers.run();  // Keep the steppers moving
    if (!check())
    {
      Utils::serialPrintf("You stupid baffoon!\n");
      return;  // Exit the function if check() fails
    }
  }

  m_Steppers.runSpeedToPosition();
}

void LeadScrewStepper::putDownObj() const
{
  long new_positions[2] = {m_LeftStepper.currentPosition() - (STEPS_PER_REVOLUTION / 8),
                              m_RightStepper.currentPosition() - (STEPS_PER_REVOLUTION / 8)};
  m_Steppers.moveTo(new_positions);

  unsigned long prevTime = millis();
  int pos = 45;

  while (pos <= 90)  // Continue until pos reaches 90
  {
    if (millis() - prevTime >= 10)  // Update servos every 10 ms
    {
      prevTime = millis(); // Reset timer

      m_LeftServo.write(R2L_CONVERT(pos));
      m_RightServo.write(pos);
      pos++;
    }

    m_Steppers.run();  // Keep the steppers moving
    if (!check())
    {
      Utils::serialPrintf("You stupid n-\n");
      return;  // Exit the function if runAndCheck() fails
    }
  }

  m_Steppers.runSpeedToPosition();
}

void LeadScrewStepper::checkBoundries() const
{
  while(true)
  {
    m_Steppers.moveTo(max_pos);
    m_Steppers.runSpeedToPosition();
    delay(1000);
    m_Steppers.moveTo(start_pos);
    m_Steppers.runSpeedToPosition();
    delay(1000);
  }
}

void LeadScrewStepper::checkServos() const
{ 
  while (true)
  { 
    for(int pos = 90; pos >= 45; pos--)
    {
      m_LeftServo.write(R2L_CONVERT(pos));
      m_RightServo.write(pos);
      delay(10);
    }

    delay(1000);

    for(int pos = 45; pos <= 90; pos++)
    {
      m_LeftServo.write(R2L_CONVERT(pos));
      m_RightServo.write(pos);
      delay(10);
    }

    delay(1000);
  }
}

void LeadScrewStepper::checkObjHandle() const
{
  long positions[2] = {-1000, -1000};
  m_Steppers.moveTo(positions);
  m_Steppers.runSpeedToPosition();
  delay(1000);
  pickUpObj();
  delay(1000);
  putDownObj();
}