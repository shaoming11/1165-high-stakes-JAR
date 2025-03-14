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
motor LF = motor(PORT17, ratio36_1, false);
motor LM = motor(PORT18, ratio18_1, true);
motor LB = motor(PORT19, ratio36_1, false);
motor RF = motor(PORT5, ratio36_1, true);
motor RM = motor(PORT2, ratio36_1, false);
motor RB = motor(PORT4, ratio36_1, true);
motor fIntake = motor(PORT14, ratio18_1, false);
motor hIntake = motor(PORT15, ratio36_1, false);
motor wallL = motor(PORT12, ratio18_1, false);
motor wallR = motor(PORT3, ratio18_1, true);
motor_group intake = motor_group(fIntake, hIntake);

inertial Gyro = inertial(PORT13);
rotation Wall = rotation(PORT19);
optical ColSort = optical(PORT6);

digital_out Clamp = digital_out(Brain.ThreeWirePort.B);
digital_out Doink = digital_out(Brain.ThreeWirePort.A);
digital_out Claw = digital_out(Brain.ThreeWirePort.E);

void vexcodeInit( void ) {
  // nothing to initialize
}