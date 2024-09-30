#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <Arduino.h>

#define SECOND 1000

typedef struct motor{
  uint8_t in1;
  uint8_t in2;
  uint8_t pwm;
} motor;

extern motor motors[4];



#endif