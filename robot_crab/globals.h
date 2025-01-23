#pragma once

#include <Arduino.h>

#define SECOND_MS 1000

#define MATH_PI 3.14159265358979

struct motor 
{
  uint8_t in1;
  uint8_t in2;
  uint8_t pwm;
};

extern const motor motors[4];

struct stepperLS
{
  uint8_t dir;
  uint8_t step;
};

extern const stepperLS leftStepper, rightStepper;