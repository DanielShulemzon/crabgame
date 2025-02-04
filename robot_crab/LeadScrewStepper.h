#pragma once

#define START_POS 0
#define MAX_POS -2000

#define RIGHT_SERVO_START 90
#define LEFT_SERVO_START 80
#define RIGHT_SERVO_END 45
#define R2L_CONVERT(deg) (170 - deg) // 10 degrees for making them parallel

#include "globals.h"
#include <AccelStepper.h>
#include <Servo.h> 

class LeadScrewStepper 
{
private:
  AccelStepper m_RightStepper, m_LeftStepper;

  Servo m_LeftServo, m_RightServo;

  uint16_t m_Rps = 200;

public:
  LeadScrewStepper(const stepperLS& leftStepper, const stepperLS& rightStepper, uint8_t serPin1, uint8_t serPin2);
  void reset() const;

  bool runAndCheck() const;

  void checkBoundries() const;

  void checkServos() const;
  
};