#include "utils.h"
#include <stdio.h>
#include <stdarg.h>

void motorsSetup(){
  for(int i = 0; i < 4; i++){
    pinMode(motors[i].in1, OUTPUT);
    pinMode(motors[i].in2, OUTPUT);
  }
}


void resetMotors(){
  for(int i = 0; i < 4; i++){
    digitalWrite(motors[i].in1, 0);
    digitalWrite(motors[i].in2, 0);
  }
}

void setMotorsSpeed(const uint8_t speed){
  for(int i = 0; i < 4; i++){
    analogWrite(motors[i].pwm, speed);
  }
}


void serialPrintf(const char *format, ...) { // for debugging
  static char buffer[100];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);
  Serial.print(buffer);
}

