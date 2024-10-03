#include "globals.h"
#include "utils.h"
#include "MotorController.h"


MotorController motorController; //handles all 4 wheels like a boss


void testDrive(){

  motorController.setSpeed(150);
  
  while(true){
    for(int i = 0; i < 4; i++){
      digitalWrite(motors[i].in1, 1);
      digitalWrite(motors[i].in2, 0);

      serialPrintf("Activated pins: %u %u", motors[i].in1, motors[i].in2);
      delay(SECOND_MS);
    }
    delay(SECOND_MS);
    motorController.resetMotors();
    delay(SECOND_MS);
  }
}


void setup() {
  Serial.begin(9600);
  motorController.setup();
  
}

void loop() {
  testDrive();

}
