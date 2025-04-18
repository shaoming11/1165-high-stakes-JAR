#include "vex.h"
#include "robot-config.h"
#include "tasks.h"

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
bool armToAlliance          = false;

static void armPID(int target){
  uint32_t now = Brain.Timer.time(msec);
  

  float kP = 0.015;

  int error = target - Wall.position(deg);
  uint32_t startTime = Brain.Timer.time(msec);

  while (abs(error) > 50){
    wallL.spin(fwd, kP*error, voltageUnits::mV);
    error = target - Wall.position(deg);
    // pros::Task::delay_until(&now, 2);
    waitUntil(2);
  }
}

void debugLoop(void *params) {
  uint32_t now = Brain.Timer.time(msec);

  while(1){
    waitUntil(20);
  }
}

void conveyorLoop(void *params) {
  uint32_t now = Brain.Timer.time(msec);
  int jamcount = 0;
  while (true) {
    if (convDir == ConveyorDirection_e::FORWARD) 
    {
      if (doColorSort 
      && ColSort.hue() > SORT_COLOUR - 20 
      && ColSort.hue() < SORT_COLOUR + 20 
      && ColSort.isNearObject()){
        jamcount = 0;
        waitUntil(50);
        hIntake.spin(directionType::rev, 12, volt);
        waitUntil(500);
        hIntake.spin(fwd, 12, volt);
      }
      //red or not detected
      else if (fabs(hIntake.torque())>=1.0 && fabs(hIntake.velocity(rpm)) <= 1 && (Wall.position(deg) > 2500 || Wall.position(deg) < 1000) && doAntiJam){
        jamcount++;
        waitUntil(10);
        if (jamcount>10){
          hIntake.setVelocity(-600, rpm);
          waitUntil(100);
          hIntake.setVelocity(600, rpm);
          
        }
      }
      else {
        jamcount = 0;
        hIntake.setVelocity(convVelocity, rpm);
        intake.setVelocity(convVelocity, rpm);
      }
    } 
    else if (convDir == BACKWARD) 
    {
        hIntake.setVelocity(-600, rpm);
        intake.setVelocity(-600, rpm);
    } 
    else if (convDir == FIRST) 
    {
      hIntake.setVelocity(0, rpm);
      intake.setVelocity(600, rpm);
    } 
    else 
    {
      hIntake.setVelocity(0, rpm);
      intake.setVelocity(0, rpm);
    }

    waitUntil(1);
  }
}

void armLoop(void *params) {
  uint32_t now = Brain.Timer.time(msec);

  while (true) {
    Brain.Screen.printAt(5, 100, "arm: %d", Wall.position(deg));
    
    if (armToLoadPos){
      armPID(1500);
      // armToLoadPos = false;
      
    } if(armToStartPos){
      armPID(100);

    } else if(armToScore){
      armPID(18750);

    } else if(armToScorePos){
      armPID(4000);

    } else if(armToAlliance){
      armPID(25000);
    }

    waitUntil(1);
  }
}