#include "LeadScrewStepper.h"


LeadScrewStepper::LeadScrewStepper(uint8_t stepPin, uint8_t dirPin)
    : stepper(AccelStepper::DRIVER, stepPin, dirPin) {
  stepper.setCurrentPosition(0);
  stepper.setMaxSpeed(8192);
  stepper.setSpeed(rpm);
  stepper.setAcceleration(1000);
}

void LeadScrewStepper::reset() {
  stepper.runToNewPosition(0);
}

bool LeadScrewStepper::runAndCheck() {
  // if out of boundries, return false.
  stepper.run();
  long currentSteps = stepper.currentPosition();
  if(currentSteps >= MAX_STEPS || currentSteps <= MIN_STEPS){
    //PANIC
    reset();
    return false;
  }
  return true;
}