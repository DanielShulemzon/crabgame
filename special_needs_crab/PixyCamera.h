#pragma once

#define CAM_PIXELS 316
#define BOX_OG_PIXELS 10

#include "globals.h"
#include <Pixy2.h>
#include <SPI.h>

enum ColorSignature
{
  OBJ_COLOR_SIGNATURE,
  DEST_COLOR_SIGNATURE,
};

extern Pixy2 pixy;

namespace PixyCamera {
  double getAngle(Block* block);

  double getDistance(Block* block);

  int16_t getPrimaryObjId();

  Block* trackBlock(uint8_t index);

  // *Block getTargetDest();
}
