#include "globals.h"
#include "utils.h"
#include "MotorController.h"
#include "PixyCamera.h"
#include "LeadScrewStepper.h"

MotorController motorController; // handles all 4 wheels like a boss
LeadScrewStepper* stepperController; // ptr to a stack allocated block for late initializing.
Pixy2 pixy;


void setup()
{
  Serial.begin(9600);
  pixy.init();
  stepperController = &LeadScrewStepper(leftStepper, rightStepper, leftServoPin, rightServoPin);
  
  // Utils::serialPrintf("entering...\n");
  // if(stepperController->closeOnObj())
  // {
  //   delay(1000);
  //   stepperController->pickUpObj();
  //   delay(1000);
  //   stepperController->putDownObj();
  // }

  stepperController->checkForceSensor();
}

void loop() 
{

}
