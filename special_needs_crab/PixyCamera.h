#pragma once

#define BOX_OG_WIDTH 10.0
#define PIXY_HEIGHT 30.0
#define PIXY_DIST_FROM_FRONT 18.0

#include "globals.h"
#include <Pixy2.h>
#include <SPI.h>

enum ColorSignature
{
  OBJ_COLOR_SIGNATURE = 1,
  DEST_COLOR_SIGNATURE = 2,
};

extern Pixy2 pixy;

namespace PixyCamera {
  double getAngle(Block* block);

  double getDistanceFromPixy(Block* block);

  double getDistanceFromRobot(Block* block);

  int16_t getPrimaryObjId();

  Block* trackBlock(int16_t index);

  // *Block getTargetDest();

  void debugPixy();
}
