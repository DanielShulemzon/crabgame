#pragma once

#include "globals.h"
#include "PixyCamera.h"
#include "LeadScrewStepper.h"
#include "MotorController.h"

enum State
{
  // looking for obj
  LOOKING_FOR_OBJ,
  // going towards an obj and picking it
  PICKING_OBJ_STAGE,
  // finding a destination and placing it
  PLACING_OBJ_STAGE,
};

extern MotorController motorController;
extern LeadScrewStepper* stepperController;
extern Pixy2 pixy;

namespace MainLoop {
  bool holding_obj = false;
  static int16_t blockIdx = -1;
  State state = LOOKING_FOR_OBJ;

  void main_loop();
};