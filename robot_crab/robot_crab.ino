#include "globals.h"
#include "utils.h"
#include "MotorController.h"
#include "PixyCamera.h"
#include "LeadScrewStepper.h"

MotorController motorController; //handles all 4 wheels like a boss
LeadScrewStepper stepperController(8, 9);
Pixy2 pixy;


void testDrive() {

  motorController.setSpeed(150);
  
  while(true){
    for(int i = 0; i < 4; i++){
      motorController.resetMotors();
      digitalWrite(motors[i].in1, 1);
      digitalWrite(motors[i].in2, 0);

      serialPrintf("Activated pins: %u %u", motors[i].in1, motors[i].in2);
      delay(SECOND_MS);
    }
  }
}

void driveInFunnyAngle() {
  motorController.setSpeed(150);
  double angle = 45;
  while(true){
    motorController.moveAtAngle(angle);
    delay(1000);
    motorController.moveAtAngle(-angle);
    delay(1000);
  }
}

void StepperBoundriesChecker() {
  while(true) {
    stepperController.stepper.runToNewPosition(MAX_STEPS);
    delay(100);
    stepperController.stepper.runToNewPosition(MIN_STEPS);
    delay(100);
  }
}


void setup() {
  Serial.begin(9600);
  motorController.setup();

  driveInFunnyAngle();
}

void loop() {

}
