// #include "LeadScrewStepperMotor.h"


// LeadScrewStepperMotor::LeadScrewStepperMotor(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4)
//     : stepper(stepsPerRevolution, in1, in2, in3, in4) {
//   stepper.setSpeed(rpm);
// }

// void LeadScrewStepperMotor::reset() {
//   stepper.step(-deltaSteps);
//   deltaSteps = 0;
// }

// void LeadScrewStepperMotor::update(int32_t error) {
//   for(uint16_t i = 0; i < error; i++) {
//     if(deltaSteps >= MAX_STEPS || deltaSteps <= -MAX_STEPS){
//       //PANIC
//       reset();
//       break;
//     }
//     deltaSteps++;
//     stepper.step(1);
//   }
// }