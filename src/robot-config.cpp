#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen.
brain  Brain;
controller Controller(primary);
controller Shao(partner);
//The motor constructor takes motors as (port, ratio, reversed), so for example
//motor LeftFront = motor(PORT1, ratio6_1, false);

//Add your devices below, and don't forget to do the same in robot-config.h:
motor LF = motor(PORT8, ratio36_1, true);
motor LM = motor(PORT9, ratio18_1, true);
motor LB = motor(PORT10, ratio36_1, false);
motor RF = motor(PORT5, ratio36_1, true);
motor RM = motor(PORT6, ratio36_1, false);
motor RB = motor(PORT7, ratio36_1, false);
motor fIntake = motor(PORT14, ratio18_1, true);
motor hIntake = motor(PORT19, ratio36_1, true);
motor wallL = motor(PORT11, ratio18_1, false);
motor wallR = motor(PORT3, ratio18_1, true);
motor_group intake = motor_group(fIntake, hIntake);

inertial Gyro = inertial(PORT16);
rotation Wall = rotation(PORT13);
optical ColSort = optical(PORT12);

digital_out Clamp = digital_out(Brain.ThreeWirePort.B);
digital_out Doink = digital_out(Brain.ThreeWirePort.A);
digital_out DoinkR = digital_out(Brain.ThreeWirePort.C);

void vexcodeInit( void ) {
  // nothing to initialize
}