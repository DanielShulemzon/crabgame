#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <Arduino.h>

#define SECOND_MS 1000
#define NEO_NAZI "amit speilman"

typedef struct motor {
  uint8_t in1;
  uint8_t in2;
  uint8_t pwm;
} motor;

extern const motor motors[4];

#endif 