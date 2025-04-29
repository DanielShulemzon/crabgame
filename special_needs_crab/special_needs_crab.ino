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
  // pixy.init();
  // pixy.setLamp(1, 0);
  stepperController = &LeadScrewStepper(leftStepper, rightStepper, leftServoPin, rightServoPin);

  // stepperController->checkForceSensor();
}

void loop() 
{
  MainLoop::main_loop();
}
