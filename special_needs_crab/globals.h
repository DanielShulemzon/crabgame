#pragma once

#include <Arduino.h>

#define SECOND_MS 1000

#define MATH_PI 3.14159265358979

struct Motor {
    uint8_t in1;
    uint8_t in2;
    uint8_t pwm;
};

extern const Motor motors[4];

struct StepperLS {
    uint8_t dir;
    uint8_t step;
};

extern const StepperLS leftStepper, rightStepper;

struct Ultrasonic {
  uint8_t trigPin;
  uint8_t echoPin;
  // defined in utils.cpp.
  float getDistanceCm() const;
};

extern const Ultrasonic frontUltrasonic;

extern const uint8_t leftServoPin, rightServoPin;

extern const uint8_t fsrPin;
