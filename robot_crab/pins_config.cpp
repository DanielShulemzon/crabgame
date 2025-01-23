#include "globals.h"

// this file contains all pins, I like.

const motor motors[4] = {
  {27, 26, 3}, // left back
  {29, 28, 4}, // right back
  {23, 22, 5}, // right front
  {25, 24, 6} // left front
};


const stepperLS leftStepper = {8, 9}, rightStepper = {10, 11};