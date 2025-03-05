#pragma once

#define CAM_PIXELS 316
#define BOX_OG_PIXELS 10

#include "globals.h"
#include <Pixy2.h>
#include <SPI.h>

namespace PixyCamera {
  double getAngle(Block* block);

  double getDistance(Block* block);
}
