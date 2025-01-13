#pragma once

#define START_POS 0
#define MAX_POS -2000

#include "globals.h"
#include <AccelStepper.h>
#include <Servo.h>

class LeadScrewStepper 
{
private:
  AccelStepper m_LeftStepper, m_RightStepper;

  Servo m_LeftServo, m_RightServo;

  uint16_t m_Rps = 200;

public:
  // left: 1, right: 2.
  LeadScrewStepper(uint8_t dirPin1, uint8_t stepPin1, uint8_t dirPin2,
                     uint8_t stepPin2, uint8_t serPin1, uint8_t serPin2);
  void reset() const;

  bool runAndCheck() const;

  void checkBoundries() const;

  void servoChecker() const;
  
};