#include "vex.h"
#include "robot-config.h"

ConveyorDirection_e convDir = STOP;
int convVelocity            = 0;
int armTimeout              = 0;
int jamTimeout              = 0;
bool doColorSort            = false;
bool doAntiJam              = false;
bool armToLoadPos           = false;
bool armToStartPos          = false;
bool armToScorePos          = false;
bool armToScore             = false;
bool armToLow               = false;

static double getWall() {
  if (Wall.position(deg) > 180) {
    return Wall.position(deg)-360;
  } else {
    return Wall.position(deg);
  }
}

static void armPID(int target){
  uint32_t now = Brain.Timer.time(msec);

  float kP = 0.25;

  int error = target - getWall();
  uint32_t startTime = Brain.Timer.time(msec);

  if (abs(error) > 1){
    wallL.spin(fwd, kP*error, voltageUnits::volt);
    error = target - getWall();
    task::sleep(2);
  }
}

int debugLoop(void *params) {
  uint32_t now = Brain.Timer.time(msec);

  while(1){
    task::sleep(20);
  }

  return 0;
}

int conveyorLoop() {
  printf("asdf");
  uint32_t now = Brain.Timer.time(msec);
  int jamcount = 0;
  while (true) {
    if (convDir == ConveyorDirection_e::FORWARD) 
    {
      if (ColSort.hue() > SORT_COLOUR - 20 && ColSort.hue() < SORT_COLOUR + 20 && doColorSort && ColSort.isNearObject()){ //  && 
        jamcount = 0;
        task::sleep(100);
        hIntake.spin(directionType::rev, 12, volt);
        task::sleep(500);
        hIntake.spin(fwd, 12, volt);
      }
      //red or not detected
      else if (fabs(hIntake.torque())>=1.0 && fabs(hIntake.velocity(rpm)) <= 1 && (Wall.position(deg) > -20 || Wall.position(deg) < -36) && doAntiJam){
        jamcount++;
        task::sleep(10);
        if (jamcount>10){
          hIntake.spin(directionType::rev, 12, volt);
          task::sleep(100);
          hIntake.spin(fwd, 12, volt);
          
        }
      } 
      // else if (doColorSort && (hIntake.torque())>=1.0 && fabs(hIntake.velocity(rpm)) <= 1 && (Wall.position(deg) > -30 || Wall.position(deg) < -26) && armToLoadPos == true) {
      //   jamcount++;
      //   task::sleep(10);
      //   if (jamcount>10){
      //     hIntake.spin(directionType::rev, 0, volt);
      //     task::sleep(50);
      //     hIntake.spin(fwd, 12, volt);
      //   }
      // }
      else { // change if (1) to else
        jamcount = 0;
        hIntake.spin(fwd, 12, volt);
      }
    } 
    else if (convDir == BACKWARD) 
    {
      hIntake.spin(directionType::rev, 12, volt);
    } 
    else 
    {
      hIntake.spin(fwd, 0, volt);
    }

    task::sleep(1);
  }

  return 0;
}

int armLoop() {
  uint32_t now = Brain.Timer.time(msec);

  while (true) {
    if ((!Controller.ButtonL1.pressing() && !Controller.ButtonL2.pressing())) {
      if (armToLoadPos){
        armPID(-28);
        // armToLoadPos = false;
      
      } else if(armToStartPos){
        armPID(0);

      } else if(armToScore){ // descore
        armPID(-165);

      } else if(armToScorePos){ // Score
        armPID(-120);

      } else if(armToLow) {
        armPID(-200);
      }
    }
    Brain.Screen.printAt(5, 180, "arm: %.2f", Wall.position(deg));

    task::sleep(1);
  }

  return 0;
}