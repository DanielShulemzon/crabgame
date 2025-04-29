#include "globals.h"

// this file contains all pins, I like.

const Motor motors[4] = {
    { 27, 26, 3 }, // left back
    { 29, 28, 4 }, // right back
    { 23, 22, 5 }, // right front
    { 25, 24, 6 } // left front
};

const StepperLS rightStepper = { 49, 9 }, leftStepper = { 10, 11 };

const uint8_t leftServoPin = 12, rightServoPin = 13;

const Ultrasonic frontUltraSonic { 42, 43 };

const uint8_t fsrPin = A0;
