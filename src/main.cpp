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
PORT13,

//Input your wheel diameter. (4" omnis are actually closer to 4.125"):
2.75,

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
PORT11,     -PORT14,

//LB:      //RB: 
PORT13,     -PORT16,

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

void autonomous(void) {
  auto_started = true;
  switch(current_auton_selection){ 
    case 0:
      //turn_test(); 
      grush_b();
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
  bool toggleClamp = 1;
  bool toggleClaw = 1;
  bool toggleDoink = 1;
  bool toggleColsort = 1; // sort red is 0, sort blue is 1
  
  double targetPos = 0;
  bool lbActive = false;
  double lbLoad = -110;
  double lbScore = -230;
  double lbZero = -10;
  double lbDescore = -440;
  double lbTime = 0;
  wallL.setVelocity(80, pct);

  // Calibrated hue values for red and blue (replace with your actual values)
  int RED_HUE = 20;    // Replace with the actual hue value for red
  int BLUE_HUE = 200; // Replace with the actual hue value for blue
  int TOLERANCE = 50; // Tolerance for hue detection (adjust as needed)
  int TARGET_HUE = BLUE_HUE;
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    // LF.setBrake(brake);
    // LM.setBrake(brake);
    // LB.setBrake(brake);
    // RF.setBrake(brake);
    // RM.setBrake(brake);
    // RB.setBrake(brake);
    wallL.setBrake(hold);
    //wallR.setBrake(hold);
    /*
    // SHAO --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // if (Shao.ButtonA.pressing()) {
    //   TARGET_HUE = toggleColsort ? BLUE_HUE : RED_HUE;
    //   toggleColsort = toggleColsort * -1 + 1;
    //   while (Shao.ButtonA.pressing()) {
    //     task::sleep(10);
    //   }
    // }
    
    if (Shao.ButtonR1.pressing()) {
      intake.spin(fwd, 12, volt);

      // // COLOUR SORTING
      // // Turn on the sensor's LED for better detection
      // ColSort.setLight(ledState::on);

      // // Get the hue value of the detected color
      // int detectedHue = ColSort.hue();
      // if (detectedHue >= TARGET_HUE - TOLERANCE && detectedHue <= TARGET_HUE + TOLERANCE) {
      //   // Action for red object (e.g., spin intake to collect)
      //   task::sleep(50);
      //   intake.stop();
      //   task::sleep(50);
      // }
    }
    
    if (Shao.ButtonR2.pressing()) {
      intake.spin(directionType::rev, 12, volt);
    }

    // SHAO LADYBROWN -------------------------------------------------------------------------------------
    if (Shao.ButtonL1.pressing()) {
      lbActive = false;
      wallL.spin(directionType::rev, 12, volt);
      wallR.spin(directionType::rev, 12, volt);
    } else if (Shao.ButtonL2.pressing()) {
      lbActive = false;
      wallL.spin(directionType::fwd, 12, volt);
      wallR.spin(directionType::fwd, 12, volt);
    }

    // LOAD LB
    if (Shao.ButtonLeft.pressing()) {
      lbActive = true;
      targetPos = lbLoad;
      wallL.spinTo(targetPos, deg, false);  // Non-blocking call
      wallR.spinTo(targetPos, deg, false);
    }

    // SCORING LB
    if (Shao.ButtonUp.pressing()) {
      lbActive = true;
      targetPos = lbScore;
      wallL.spinTo(targetPos, deg, false);  // Non-blocking call
      wallR.spinTo(targetPos, deg, false);
    }

    // DESCORE LB
    if (Shao.ButtonX.pressing()) {
      lbActive = true;
      targetPos = lbDescore;
      wallL.spinTo(targetPos, deg, false);  // Non-blocking call
      wallR.spinTo(targetPos, deg, false);
    }

    if (Shao.ButtonDown.pressing()) {
      lbActive = false;
      wallL.resetPosition();
      wallR.resetPosition();
    }
    */


    // MAIN CONTROLLER -------------------------------------------------------------------------------------
    if (Controller.ButtonR1.pressing()) {
      intake.spin(fwd, 12, volt);

      // // Turn on the sensor's LED for better detection
      // ColSort.setLight(ledState::on);

      // // Get the hue value of the detected color
      // int detectedHue = ColSort.hue();

      // // COLOUR SORTING
      // TARGET_HUE = (toggleColsort) ? RED_HUE : BLUE_HUE;
      // if (detectedHue < 40 && TARGET_HUE == RED_HUE) {
      //   // Action for red object (e.g., spin intake to collect)
      //   task::sleep(50);
      //   intake.stop();
      //   task::sleep(50);       
      // }
      // if (detectedHue > 180) {
      //   // Action for red object (e.g., spin intake to collect)
      //   task::sleep(50);
      //   intake.stop();
      //   task::sleep(50); 
      // }
      // if (detectedHue >= TARGET_HUE - TOLERANCE && detectedHue <= TARGET_HUE + TOLERANCE) {
      //   // Action for red object (e.g., spin intake to collect)
      //   task::sleep(50);
      //   intake.stop();
      //   task::sleep(50);
      // }
    }
    
    if (Controller.ButtonR2.pressing()) {
      intake.spin(directionType::rev, 12, volt);
    }
    
    if ((!Shao.ButtonR1.pressing() && !Shao.ButtonR2.pressing()) && (!Controller.ButtonR1.pressing() && !Controller.ButtonR2.pressing())) {
      intake.spin(fwd, 0, volt);
    }

    // LADY BROWN --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    Brain.Screen.printAt(5, 200, "ANGLE: %f", wallL.position(deg));
    
    if (Controller.ButtonL1.pressing()) {
      lbActive = false;
      wallL.spin(directionType::rev, 12, volt);
      wallR.spin(directionType::rev, 12, volt);
    } else if (Controller.ButtonL2.pressing()) {
      lbActive = true;
      targetPos = lbZero;
      wallL.spinTo(targetPos, deg, false);  // Non-blocking call
      wallR.spinTo(targetPos, deg, false);
    } 
    
    if ((!Controller.ButtonL1.pressing() && !Controller.ButtonL2.pressing() && !Shao.ButtonL1.pressing() && !Shao.ButtonL2.pressing() && !lbActive)){
      // Stop the motors when no button is pressed
      wallL.stop();
      wallR.stop();
    }

    // LOAD LB
    if (Controller.ButtonDown.pressing()) {
      lbActive = true;
      targetPos = lbLoad;
      wallL.spinTo(targetPos, deg, false);  // Non-blocking call
      wallR.spinTo(targetPos, deg, false);
    }

    // ZERO LB
    if (Controller.ButtonLeft.pressing()) {
      lbActive = true;
      targetPos = lbZero;
      wallL.spinTo(targetPos, deg, false);  // Non-blocking call
      wallR.spinTo(targetPos, deg, false);
    }

    // DESCORE LB
    if (Controller.ButtonRight.pressing()) {
      lbActive = true;
      targetPos = lbDescore;
      wallL.spinTo(targetPos, deg, false);  // Non-blocking call
      wallR.spinTo(targetPos, deg, false);
    }

    if (Controller.ButtonUp.pressing()) {
      lbActive = false;
      wallL.resetPosition();
      wallR.resetPosition();
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

    // COLOUR SORT TOGGLE
    if (Controller.ButtonA.pressing()) {
      toggleColsort = toggleColsort * -1 + 1;
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