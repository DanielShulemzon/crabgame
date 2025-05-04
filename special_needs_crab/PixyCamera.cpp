#include "PixyCamera.h"


double PixyCamera::getAngle(Block *block) 
{
  double dx = static_cast<double>(block->m_x) - (static_cast<double>(pixy.frameWidth) / 2.0);

  const double FOV = 75;
  double anglePerPixel = FOV / static_cast<double>(pixy.frameWidth);

  return dx * anglePerPixel;
}

double PixyCamera::getDistanceFromPixy(Block *block) 
{
  // see explaination in docos.
  double screenWidth = static_cast<double>(pixy.frameWidth) / block->m_width * BOX_OG_WIDTH;
  return screenWidth / 2.0 * sqrt(3);
}

double PixyCamera::getDistanceFromRobot(Block *block) 
{
  // see explaination in docos.
  double distFromPixy = getDistanceFromPixy(block);
  double vertDist = sqrt(distFromPixy*distFromPixy - PIXY_HEIGHT*PIXY_HEIGHT);
  return vertDist - PIXY_DIST_FROM_FRONT;
}

// Take the biggest block (of the correct color signature) that's been around for at least 10 frames
// and return its index, otherwise return -1
int16_t PixyCamera::getPrimaryObjId()
{
  if (!pixy.ccc.numBlocks)
    return -1;

  for (int i = 0; i < pixy.ccc.numBlocks; ++i)
  {
    if (pixy.ccc.blocks[i].m_signature == OBJ_COLOR_SIGNATURE) {
      if (pixy.ccc.blocks[i].m_age>30)
        return pixy.ccc.blocks[0].m_index;
      else return -1; // not a bug, a feature.
    }
  }
  return -1;
}

Block* PixyCamera::trackBlock(int16_t index)
{
  uint8_t i;

  for (i=0; i<pixy.ccc.numBlocks; i++)
  {
    if (index==pixy.ccc.blocks[i].m_index)
      return &pixy.ccc.blocks[i];
  }

  return NULL;
}


void PixyCamera::debugPixy()
{
  pixy.ccc.getBlocks();

  int16_t objId = getPrimaryObjId();
  if (objId == -1) {
    Serial.println("No consistant obj was found.");
  } else {
    Block* b = trackBlock(objId);
    b->print();
  }
}