#include "PixyCamera.h"


double PixyCamera::getAngle(Block *block) 
{
  return atan((block->m_x - (CAM_PIXELS / 2)) * 158 * sqrt(3)) * 180 / PI;
}

double PixyCamera::getDistance(Block *block) 
{
  double screenWidth = (double) CAM_PIXELS / block->m_width * BOX_OG_PIXELS;
  return screenWidth / 2 * sqrt(3);
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
      else return -1;
    }
  }
  return -1;
}

Block* PixyCamera::trackBlock(uint8_t index)
{
  uint8_t i;

  for (i=0; i<pixy.ccc.numBlocks; i++)
  {
    if (index==pixy.ccc.blocks[i].m_index)
      return &pixy.ccc.blocks[i];
  }

  return NULL;
}