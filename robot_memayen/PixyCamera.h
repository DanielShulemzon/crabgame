#ifndef _PIXYCAMERA_H
#define _PIXYCAMERA_H

#include <SPI.h>
#include <Pixy2.h>
#include "globals.h"

class PixyCamera {
private:
  Pixy2 pixy;

public:
  PixyCamera();

}

#endif