#ifndef _PIXYCAMERA_H
#define _PIXYCAMERA_H

#define CAM_PIXELS 316
#define BOX_OG_PIXELS 10

#include <SPI.h>
#include <Pixy2.h>
#include "globals.h"

namespace PixyCamera {

  double getAngle(Block *block);

  double getDistance(Block *block);

}

#endif