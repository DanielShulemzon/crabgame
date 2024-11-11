#include "globals.h"
#include "utils.h"
#include "MotorController.h"
#include "PixyCamera.h"
#include "LeadScrewStepper.h"

MotorController motorController; // handles all 4 wheels like a boss
LeadScrewStepper stepperController(8, 9, 10); // handles my GalvenizedSquaredLeadScrew like a bosch.
Pixy2 pixy;


void driveInFunnyAngle() 
{
  motorController.setSpeed(150);
  double angle = 45;
  while(true)
  {
    motorController.moveAtAngle(angle);
    delay(1000);
    motorController.moveAtAngle(-angle);
    delay(1000);
  }
}


void setup() 
{
  Serial.begin(9600);

  // driveInFunnyAngle();
}

void loop() 
{

}
