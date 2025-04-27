#include "vex.h"

using namespace vex;
competition Competition;

/*---------------------------------------------------------------------------*/
/*                             VEXcode Config                                */
/*                                                                           */
/*  Before you do anything else, start by configuring your motors and        */
/*  sensors. In VEXcode Pro V5, you can do this using the graphical          */
/*  configurer port icon at the top right. In the VSCode extension, you'll   */
/*  need to go to robot-config.cpp and robot-config.h and create the         */
/*  motors yourself by following the style shown. All motors must be         */
/*  properly reversed, meaning the drive should drive forward when all       */
/*  motors spin forward.                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                             JAR-Template Config                           */
/*                                                                           */
/*  Where all the magic happens. Follow the instructions below to input      */
/*  all the physical constants and values for your robot. You should         */
/*  already have configured your motors.                                     */
/*---------------------------------------------------------------------------*/

Drive chassis(

//Pick your drive setup from the list below:
//ZERO_TRACKER_NO_ODOM
//ZERO_TRACKER_ODOM
//TANK_ONE_FORWARD_ENCODER
//TANK_ONE_FORWARD_ROTATION
//TANK_ONE_SIDEWAYS_ENCODER
//TANK_ONE_SIDEWAYS_ROTATION
//TANK_TWO_ENCODER
//TANK_TWO_ROTATION
//HOLONOMIC_TWO_ENCODER
//HOLONOMIC_TWO_ROTATION
//
//Write it here:
ZERO_TRACKER_NO_ODOM,

//Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
//You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".

//Left Motors:
motor_group(LF, LM, LB),

//Right Motors:
motor_group(RF, RM, RB),

//Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
PORT17,

//Input your wheel diameter. (4" omnis are actually closer to 4.125"):
16.5,

//External ratio, must be in decimal, in the format of input teeth/output teeth.
//If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
//If the motor drives the wheel directly, this value is 1:
1,

//Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
//For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
360,

/*---------------------------------------------------------------------------*/
/*                                  PAUSE!                                   */
/*                                                                           */
/*  The rest of the drive constructor is for robots using POSITION TRACKING. */
/*  If you are not using position tracking, leave the rest of the values as  */
/*  they are.                                                                */
/*---------------------------------------------------------------------------*/

//If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

//FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
//LF:      //RF:    
PORT5,     -PORT8,

//LB:      //RB: 
PORT7,     -PORT10,

//If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
//If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
//If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
0,

//Input the Forward Tracker diameter (reverse it to make the direction switch):
2.75,

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
//This distance is in inches:
0,

//Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
PORT18,

//Sideways tracker diameter (reverse to make the direction switch):
-2,

//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
2

);

int current_auton_selection = 0;
bool auto_started = false;

/**
 * Function before autonomous. It prints the current auton number on the screen
 * and tapping the screen cycles the selected auton by 1. Add anything else you
 * may need, like resetting pneumatic components. You can rename these autons to
 * be more descriptive, if you like.
 */

void pre_auton() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  default_constants();
  ColSort.integrationTime(10);
  Gyro.calibrate();
  while (Gyro.isCalibrating()) { // Wait for calibration to finish
    task::sleep(100); // Prevent CPU overload
  }
  task::sleep(500);

  while(!auto_started){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5, 20, "JAR Template v1.2.0");
    Brain.Screen.printAt(5, 40, "Battery Percentage:");
    Brain.Screen.printAt(5, 60, "%d", Brain.Battery.capacity());
    Brain.Screen.printAt(5, 80, "Chassis Heading Reading:");
    Brain.Screen.printAt(5, 100, "%f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5, 160, "Vertical Position:");
    Brain.Screen.printAt(5, 180, "%f", (chassis.get_left_position_in()+chassis.get_right_position_in())/2.0);
    Brain.Screen.printAt(5, 120, "Selected Auton:");
    switch(current_auton_selection){
      case 0:
        Brain.Screen.printAt(5, 140, "Auton 1");
        break;
      case 1:
        Brain.Screen.printAt(5, 140, "Auton 2");
        break;
      case 2:
        Brain.Screen.printAt(5, 140, "Auton 3");
        break;
      case 3:
        Brain.Screen.printAt(5, 140, "Auton 4");
        break;
      case 4:
        Brain.Screen.printAt(5, 140, "Auton 5");
        break;
      case 5:
        Brain.Screen.printAt(5, 140, "Auton 6");
        break;
      case 6:
        Brain.Screen.printAt(5, 140, "Auton 7");
        break;
      case 7:
        Brain.Screen.printAt(5, 140, "Auton 8");
        break;
    }
    if(Brain.Screen.pressing()){
      while(Brain.Screen.pressing()) {}
      current_auton_selection ++;
    } else if (current_auton_selection == 8){
      current_auton_selection = 0;
    }
    task::sleep(10);
  }
}

/**
 * Auton function, which runs the selected auton. Case 0 is the default,
 * and will run in the brain screen goes untouched during preauton. Replace
 * drive_test(), for example, with your own auton function you created in
 * autons.cpp and declared in autons.h.
 */

 // autonomous1

void autonomous(void) {
  task ConveyorLoop = task(conveyorLoop);
  task ArmLoop = task(armLoop);

  Wall.setPosition(0, deg);

  doColorSort   = true;
  doAntiJam     = true;

  armToLoadPos           = false;
  armToStartPos          = false;
  armToScorePos          = false;
  armToScore             = false;

  auto_started = true;
  switch(current_auton_selection){ 
    case 0:
      //swing_test();
      awp_goal_r();
      break;
    case 1:         
      drive_test();
      break;
    case 2:
      turn_test();
      break;
    case 3:
      swing_test();
      break;
    case 4:
      full_test();
      break;
    case 5:
      odom_test();
      break;
    case 6:
      tank_odom_test();
      break;
    case 7:
      holonomic_odom_test();
      break;
 }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop

  task conveyorTask = task(conveyorLoop);
  task armTask = task(armLoop);

  doColorSort   = true;
  doAntiJam     = false;
  armToLoadPos           = false;
  armToStartPos          = false;
  armToScorePos          = false;
  armToScore             = false;

  bool toggleClamp = 1;
  bool toggleClaw = 1;
  bool toggleDoink = 1;
  bool toggleDoinkR = 1;
  
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    wallL.setBrake(hold);
    //printf("Inertial Heading: %.2f\n", Gyro.heading());

    // MAIN CONTROLLER -------------------------------------------------------------------------------------
    if (Controller.ButtonR1.pressing()) {
      convDir = FORWARD;
      //intake.spin(fwd, 12, volt);
    }
    
    else if (Controller.ButtonR2.pressing()) {
      convDir = BACKWARD;
      //intake.spin(directionType::rev, 12, volt);
    }
    
    if (!Controller.ButtonR1.pressing() && !Controller.ButtonR2.pressing()) {
      convDir = STOP;
    }
    
    if (Controller.ButtonL1.pressing()) {
      armToLoadPos           = false;
      armToStartPos          = false;
      armToScorePos          = false;
      armToScore             = false; 

      wallL.spin(directionType::rev, 12, volt);
      wallR.spin(directionType::rev, 12, volt);
    } else if (Controller.ButtonL2.pressing()) {
      armToLoadPos           = false;
      armToStartPos          = false;
      armToScorePos          = false;
      armToScore             = false;

      wallL.spin(directionType::fwd, 12, volt);
      wallR.spin(directionType::fwd, 12, volt);
    } 
    
    if ((!Controller.ButtonL1.pressing() && !Controller.ButtonL2.pressing())){
      // Stop the motors when no button is pressed
      wallL.stop();
      wallR.stop();
    }

    // LOAD LB
    if (Controller.ButtonDown.pressing()) {
      armToLoadPos           = true;
      armToStartPos          = false;
      armToScorePos          = false;
      armToScore             = false;
    }

    // ZERO LB
    if (Controller.ButtonLeft.pressing()) {

    }

    // DESCORE LB
    if (Controller.ButtonRight.pressing()) {
      armToLoadPos           = false;
      armToStartPos          = false;
      armToScorePos          = true;
      armToScore             = false;
    }

    if (Controller.ButtonUp.pressing()) {
    }

    // PNEUMATICS -------------------------------------------------------------------------------------

    // CLAMP
    if (Controller.ButtonB.pressing()) {
      Clamp.set(toggleClamp);
      toggleClamp = toggleClamp * -1 + 1;
      while (Controller.ButtonB.pressing()) {
        task::sleep(10);
      }
    }

    // DOINKER
    if (Controller.ButtonY.pressing()) {
      Doink.set(toggleDoink);
      toggleDoink = toggleDoink * -1 + 1;
      while (Controller.ButtonY.pressing()) {
        task::sleep(10);
      }
    } 

    // Doinker
    if (Controller.ButtonA.pressing()) {
      DoinkR.set(toggleDoinkR);
      toggleDoinkR = toggleDoinkR * -1 + 1;
      while (Controller.ButtonA.pressing()) {
        task::sleep(10);
      }
    } 
    //Replace this line with chassis.control_tank(); for tank drive 
    //or chassis.control_holonomic(); for holo drive.
    chassis.control_arcade();
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}