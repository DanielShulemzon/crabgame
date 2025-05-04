#include "PixyCamera.h"
#include "ErgoMechCrab.h"
#include "utils.h"


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
        motorController.resetMotors();
        state = PICKING_OBJ_STAGE;
      }
      else {
        motorController.spinInPlace();
      }
      break;

    case PICKING_OBJ_STAGE:
      // this part is blocking.
      delay(1000);

      // first reach the object, if lost revert to LOOKING_FOR_OBJ
      if (!moveToObj())
      {
        // means we lost the object
        state = LOOKING_FOR_OBJ;
        break;
      }
      delay(1000);

      // orient the robot to face the object.
      if (!fixRobotOrientation())
      {
        // means we lost the object
        state = LOOKING_FOR_OBJ;
        break;
      }

      spinToObj(); // fix orientation

      delay(1000);
      // reach a distance of approximately 0 from the obj.
      if (!approachObj())
      {
        // something went wrong
        state = LOOKING_FOR_OBJ;
        break;
      }

      // close hands on obj
      if (!stepperController->closeOnObj())
      {
        // shouldn't really reach here
        state = LOOKING_FOR_OBJ;
        break;
      }

      stepperController->pickUpObj();
      state = PLACING_OBJ_STAGE;
      break;

    case PLACING_OBJ_STAGE:
      // this part is also blocking.
      delay(1000);
      cheer();
      break;
  }
}

// returns false if lost object
bool MainLoop::moveToObj(double dist = 20)
{
  // spin to face block
  double angle, pixyRead, ultrasonicRead;
  uint8_t counter = 0;

  spinToObj();

  delay(1000);
  // go to ball
  while (true)
  {
    pixy.ccc.getBlocks();
    if (!pixy.ccc.numBlocks) {
      // lost ball
      motorController.resetMotors();
      return false;
    }
    currBlock = &pixy.ccc.blocks[0];

    angle = PixyCamera::getAngle(currBlock);
    motorController.moveAtAngle(angle);

    pixyRead = PixyCamera::getDistanceFromRobot(currBlock);
    ultrasonicRead = frontUltrasonic.getDistanceFromRobot();
    
    if (pixyRead < 20 || ultrasonicRead < 20)
    {
      counter++;
      if (counter >= 5) {
        // only return true after 5 consecutive frames to avoid random reads.
        motorController.resetMotors();
        return true;
      }
    } else {
      counter = 0;
      continue;
    }
  } 
  return true;
}

bool MainLoop::fixRobotOrientation()
{
  // random ultrasonic sensor values mean we are not facing correctly the object
  uint8_t counter = 0;
  motorController.spinAroundObj();
  while (true)
  {
    pixy.ccc.getBlocks();
    if (!pixy.ccc.numBlocks) {
      // lost ball
      return false;
    }
    currBlock = &pixy.ccc.blocks[0];

    double pixyRead = PixyCamera::getDistanceFromRobot(currBlock);
    double ultrasonicRead = frontUltrasonic.getDistanceFromRobot();
    if (Utils::matchingDistance(pixyRead, ultrasonicRead))
    {
      counter++;
      if (counter > 5)
      {
        motorController.resetMotors();
        return true;
      }
    }
    else {
      counter = 0;
      continue;
    }
  }
  return true;
}

bool MainLoop::approachObj()
{
  double ultrasonicRead;
  motorController.setSpeed(60); // temporary
  motorController.moveAtAngle(0);
  while ((ultrasonicRead = frontUltrasonic.getDistanceFromRobot()) > 0.5)
  {
    if (ultrasonicRead > 20) {
      // something has gone wrong
      motorController.setSpeed(DEFAULT_SPEED); // revert
      state = LOOKING_FOR_OBJ;
      return false;
    }
    Serial.println(ultrasonicRead);
    delay(2);
  }
  motorController.resetMotors();
  motorController.setSpeed(DEFAULT_SPEED); // revert
  return true;
}

void MainLoop::spinToObj()
{
  double angle;

  blockIdx = pixy.ccc.blocks[0].m_index;

  do {
    pixy.ccc.getBlocks();
    if (!pixy.ccc.numBlocks)
    {
      // lost ball
      motorController.resetMotors();
      return;
    }
    else
    {
      currBlock = &pixy.ccc.blocks[0];
      angle = PixyCamera::getAngle(currBlock);
      bool dir = angle > 0;
      motorController.spinInPlace(dir);
    }
  } while (abs(angle) > 2);
  blockIdx = currBlock->m_index;
  motorController.resetMotors();
}

void MainLoop::cheer()
{
  while (true) {
    stepperController->pickUpObj();
    stepperController->putDownObj();
  }
}