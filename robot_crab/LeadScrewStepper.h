#pragma once

#define MAX_STEPS 1000
#define MIN_STEPS -500

#include "globals.h"
#include <AccelStepper.h>
#include <Servo.h>

class LeadScrewStepper 
{
private:
  AccelStepper m_Stepper;
  Servo m_Servo;

  uint16_t m_Rps = 500;

public:
  LeadScrewStepper(uint8_t stepPin, uint8_t dirPin, uint8_t serPin);

  void reset() const;

  bool runAndCheck() const;

  void checkBoundries() const;

  void servoChecker() const;
  
};