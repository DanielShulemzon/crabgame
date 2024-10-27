#ifndef _LEADSCREWSTEPPER_H
#define _LEADSCREWSTEPPER_H

#define MAX_STEPS 1000
#define MIN_STEPS -500

#include "globals.h"
#include <AccelStepper.h>

class LeadScrewStepper {
private:
  uint16_t stepsPerRevolution = 2048;
  uint16_t rpm = 500;


public:
  AccelStepper stepper;

  LeadScrewStepper(uint8_t stepPin, uint8_t dirPin);

  void reset();

  bool runAndCheck();
  
};




#endif