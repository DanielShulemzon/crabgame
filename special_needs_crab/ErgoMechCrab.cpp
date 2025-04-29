#include "PixyCamera.h"
#include "ErgoMechCrab.h"


namespace MainLoop {
  bool holding_obj = false;
  static int16_t blockIdx = -1;
  State state = LOOKING_FOR_OBJ;
  Block* currBlock;
}



// algorithm:
// 1. spin around to find object.
// 2. go to the object and face it.
// 3. loop around the object and find it's ideal point.
// 4. go to the object and pick it up.
// 5. be happy.
void MainLoop::main_loop()
{
  switch (state)
  {
    case LOOKING_FOR_OBJ:
      pixy.ccc.getBlocks();
      if ((blockIdx = PixyCamera::getPrimaryObjId()) != -1)
      {
        // found out object
        currBlock = PixyCamera::trackBlock(blockIdx);
        state = PICKING_OBJ_STAGE;
      }
      else {
        motorController.spinInPlace();
      }
      break;

    case PICKING_OBJ_STAGE:
      // this part is blocking.

      // first reach the object, if lost revert to LOOKING_FOR_OBJ
      if (!moveToBlock())
      {
        // means we lost the object
        state = LOOKING_FOR_OBJ;
        break;
      }

      

      // Still not implimented Tatiana don't be mad 


    case PLACING_OBJ_STAGE:
      // this part is also blocking.

      // Still not implimented Tatiana don't be mad.
      break;
  }
}

// returns false if lost block
bool MainLoop::moveToBlock(double dist = 20)
{
  while (true)
  {
    pixy.ccc.getBlocks();
    currBlock = PixyCamera::trackBlock(blockIdx);
    if (!currBlock)
    {
      // lost ball
      return false;
    }
    else if (PixyCamera::getDistance(currBlock) < dist)
    {
      //reched close enough to ball
      return true;
    }
  } 
  return true;
}