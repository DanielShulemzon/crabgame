#pragma once

#define RIGHT_SERVO_START 90
#define LEFT_SERVO_START 80
#define RIGHT_SERVO_END 45
#define R2L_CONVERT(deg) (170 - deg) // 10 degrees for making them parallel

#include "globals.h"
#include "DualSteppers.h"
#include <AccelStepper.h>
#include <Servo.h> 

class LeadScrewStepper 
{
public:
  AccelStepper m_RightStepper, m_LeftStepper;
  DualSteppers m_Steppers;
private:
  Servo m_LeftServo, m_RightServo;

public:
  LeadScrewStepper(const stepperLS& leftStepper, const stepperLS& rightStepper, uint8_t serPin1, uint8_t serPin2); \

  bool closeOnObj() const;

  void pickUpObj() const;

  void putDownObj() const;

  void checkBoundaries() const;

  void checkServos() const;

  void checkObjHandle() const;

  void checkForceSensor() const;
};