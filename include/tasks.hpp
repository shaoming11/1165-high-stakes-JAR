#pragma once

// 210 for blue
// 20 for red
constexpr int SORT_COLOUR = 20;

typedef enum { 
  FORWARD = 0, 
  BACKWARD, 
  STOP,
  FIRST
} ConveyorDirection_e;

extern ConveyorDirection_e convDir;
extern int convVelocity;
extern int armTimeout;
extern int jamTimeout;
extern bool doColorSort;
extern bool doAntiJam;
extern bool armToLoadPos;
extern bool armToStartPos;
extern bool armToScore;
extern bool armToScorePos;
extern bool armToAlliance;

void debugLoop(void* params);
void conveyorLoop();
void armLoop(void* params);