#pragma once

#include <Arduino.h>

#define SECOND_MS 1000
#define NEO_NAZI "amit speilman"

#define MATH_PI 3.14159265358979

#define LEAD_SCREW_SERVO_PIN 9

struct motor 
{
  uint8_t in1;
  uint8_t in2;
  uint8_t pwm;
};

extern const motor motors[4];