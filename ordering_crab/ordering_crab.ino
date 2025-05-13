#include "globals.h"
#include "utils.h"
#include "MotorController.h"
#include "PixyCamera.h"
#include "LeadScrewStepper.h"
#include "ErgoMechCrab.h"

MotorController motorController; // handles all 4 wheels like a boss
LeadScrewStepper* stepperController; // ptr to a stack allocated block for late initializing.
Pixy2 pixy;


void setup()
{
  Serial.begin(9600);

  frontUltrasonic.setup();

  delay(50);
  pixy.init();
  pixy.setLamp(1, 0);

  static LeadScrewStepper stepper(leftStepper, rightStepper, leftServoPin, rightServoPin);
  stepperController = &stepper;

  // frontUltrasonic.test();
  // stepperController->checkForceSensor();
  // motorController.spinAroundObj();
  // Utils::testPixyUltrasonicError();
}

void loop() 
{
  MainLoop::main_loop();
}
