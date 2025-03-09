#include "LeadScrewStepper.h"
#include "utils.h"


LeadScrewStepper::LeadScrewStepper(const stepperLS& leftStepper, const stepperLS& rightStepper,
                                    uint8_t leftServoPin, uint8_t rightServoPin) :
      m_LeftStepper(AccelStepper::DRIVER, leftStepper.step, leftStepper.dir),
      m_RightStepper(AccelStepper::DRIVER, rightStepper.step, rightStepper.dir),
      m_Steppers(m_LeftStepper, m_RightStepper) {

  m_LeftServo.attach(leftServoPin);
  m_RightServo.attach(rightServoPin);

  m_LeftServo.write(LEFT_SERVO_START);
  m_RightServo.write(RIGHT_SERVO_START);
  delay(1000);

}

bool LeadScrewStepper::closeOnObj() const
{
  int read;
  m_Steppers.moveTo(MAX_POS);
  while (m_Steppers.run())
  {
    read = Utils::getFsrNewton();
    // Utils::serialPrintf("1: %d 2: %d, also 2 moves to: %d\n", m_LeftStepper.currentPosition(), m_RightStepper.currentPosition(), m_LeftStepper.targetPosition());
    if (read >= 10) break;
  }
  return read >= 10;
}

void LeadScrewStepper::pickUpObj() const
{
  m_Steppers.setSpeed(50.0);
  m_Steppers.moveTo(m_Steppers.currentPosition() - (STEPS_PER_REVOLUTION / 8));
  
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

    if (!m_Steppers.run())  // Keep the steppers moving
    {
      Utils::serialPrintf("You baffoon!\n");
      return;  // Exit the function if check() fails
    }
  }

  m_Steppers.runUntilFinished();
  m_Steppers.setSpeed(DEFAULT_SPEED);

}

void LeadScrewStepper::putDownObj() const
{
  m_Steppers.setSpeed(50.0);
  m_Steppers.moveTo(m_Steppers.currentPosition() + (STEPS_PER_REVOLUTION / 8));

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

    if (!m_Steppers.run())  // Keep the steppers moving
    {
      Utils::serialPrintf("You baffoon!\n");
      return;  // Exit the function if check() fails
    }
  }

  m_Steppers.runUntilFinished();
  m_Steppers.setSpeed(DEFAULT_SPEED);
}

void LeadScrewStepper::checkBoundaries() const
{
  while(true)
  {
    m_Steppers.moveTo(MAX_POS);
    Serial.println("stats: ");
    Serial.println(m_Steppers.currentPosition());
    Serial.println(m_Steppers.speed());
    m_Steppers.runUntilFinished();
    delay(1000);
    m_Steppers.moveTo(START_POS);
    m_Steppers.runUntilFinished();
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
  m_Steppers.moveTo(-1000);
  m_Steppers.runUntilFinished();
  delay(1000);
  pickUpObj();
  delay(1000);
  putDownObj();
}