#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen.
brain  Brain;
controller Controller;
//The motor constructor takes motors as (port, ratio, reversed), so for example
//motor LeftFront = motor(PORT1, ratio6_1, false);

//Add your devices below, and don't forget to do the same in robot-config.h:
motor LF = motor(PORT11, ratio36_1, false);
motor LM = motor(PORT12, ratio36_1, false);
motor LB = motor(PORT13, ratio36_1, false);
motor RF = motor(PORT14, ratio36_1, true);
motor RM = motor(PORT15, ratio36_1, true);
motor RB = motor(PORT16, ratio36_1, true);
motor intakeL = motor(PORT18, ratio36_1, false);
motor intakeR = motor(PORT3, ratio36_1, false);
motor wallL = motor(PORT20, ratio18_1, false);
motor wallR = motor(PORT17, ratio18_1, true);
motor_group intake = motor_group(intakeL, intakeR);

inertial Gyro = inertial(PORT2);
rotation Wall = rotation(PORT19);
vision Rings = vision(PORT1);

digital_out Clamp = digital_out(Brain.ThreeWirePort.A);
digital_out Doink = digital_out(Brain.ThreeWirePort.B);
digital_out Claw = digital_out(Brain.ThreeWirePort.E);

void vexcodeInit( void ) {
  // nothing to initialize
}