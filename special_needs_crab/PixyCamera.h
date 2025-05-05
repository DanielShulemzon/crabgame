#pragma once

#define NUMBER_OF_OBJECTS 2
#define BOX_OG_WIDTH 10.0
#define PIXY_HEIGHT 30.0
#define PIXY_DIST_FROM_FRONT 18.0

#include "globals.h"
#include <Pixy2.h>

enum ColorSignature
{
  PURPLE_COLOR_SIGNATURE = 1,
  RED_COLOR_SIGNATURE = 2,
};

struct ObjectData {
  int16_t signature;
  uint16_t width;
};

extern Pixy2 pixy;

extern ObjectData objects[NUMBER_OF_OBJECTS];

namespace PixyCamera {

  double getAngle(Block* block);

  double getDistanceFromPixy(Block* block, ObjectData* objectData);

  double getDistanceFromRobot(Block* block, ObjectData* objectData);

  int16_t getPrimaryObjId();

  bool isObject(Block* block);

  Block* getBiggestOfSignature(int16_t signature);

  Block* trackBlock(int16_t index);

  // *Block getTargetDest();

  void debugPixy();
}
