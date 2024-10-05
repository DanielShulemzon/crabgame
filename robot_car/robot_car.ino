#include "globals.h"
#include "utils.h"
#include "MotorController.h"
#include "Pixy2.h"

MotorController motorController; //handles all 4 wheels like a boss

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
  double angle = 45;
  while(true){
    if(angle == -45) {
      angle = 45;
    }
    else{
      angle -= 5;
    }
    motorController.moveAtAngle(angle);
    delay(100);
  }
}


void setup() {
  Serial.begin(9600);
  motorController.setup();
  testDrive();
}

void loop() {

}
