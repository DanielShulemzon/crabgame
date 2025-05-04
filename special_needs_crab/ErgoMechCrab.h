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
  extern bool holding_obj;
  extern int16_t blockIdx;
  extern State state;
  extern Block* currBlock;

  void main_loop();

  bool moveToObj(double dist = 20);

  bool fixRobotOrientation();
  
  bool approachObj();

  void spinToObj();

  void cheer();
};