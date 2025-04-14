#include "PixyCamera.h"
#include "ErgoMechCrab.h"


// algorithm:
// 1. spin around to find object.
// 2. go to the object and face it.
// 3. loop around the object and find it's ideal point.
// 4. go to the object and pick it up.
// 5. be happy.
void MainLoop::main_loop()
{
  Block* currBlock=NULL;
  pixy.ccc.getBlocks();

  switch (state)
  {
    case LOOKING_FOR_OBJ:
      if ((blockIdx = PixyCamera::getPrimaryObjId()) != -1)
      {
        state = PICKING_OBJ_STAGE;
      } else {
        motorController.spinInPlace();
      }
      break;

    case PICKING_OBJ_STAGE:
      // if lost obj revert to LOOKING_FOR_BALL
      currBlock = PixyCamera::trackBlock(blockIdx)
      if (currBlock) {
        
      }
  }
}

// returns false if lost block
bool moveToBlock(double dist = 10)
{
  currBlock = PixyCamera::trackBlock(MainLoop::blockIdx);

  if (currBlock)
  {
    
  }
}