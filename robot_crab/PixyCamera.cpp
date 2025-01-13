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