#include "vex.h"

/**
 * Resets the constants for auton movement.
 * Modify these to change the default behavior of functions like
 * drive_distance(). For explanations of the difference between
 * drive, heading, turning, and swinging, as well as the PID and
 * exit conditions, check the docs.
 */

void ladyBrown(double targetDegrees) {
  // Move Lady Brown Mechanism to a specific position (e.g., 90 degrees)
  double kP = 0.5; // Proportional gain (tune this value)
  double tolerance = 1.0; // Allowable error in degrees

  double currentPosition = Wall.position(degrees);

  while (abs(currentPosition - targetDegrees) > tolerance) {
      double error = targetDegrees - currentPosition;

      // Calculate motor power based on the error
      double motorPower = error * kP;

      // Limit motor power to avoid excessive speeds
      if (motorPower > 100) motorPower = 100;
      if (motorPower < -100) motorPower = -100;

      // Set motor direction and power
      wallL.spin(vex::directionType::fwd, motorPower, vex::velocityUnits::pct);
      wallR.spin(vex::directionType::fwd, motorPower, vex::velocityUnits::pct);

      // Update current position
      currentPosition = Wall.position(degrees);

      // Add a short delay to prevent CPU overload
      task::sleep(20);
  }

  // Stop the motors once the target is reached
  wallL.stop(hold);
  wallR.stop(hold);
    // double currentPosition = Wall.position(degrees);
    // while (abs(currentPosition - targetDegrees) > 5) { // Allow some tolerance
    //     if (currentPosition < targetDegrees) {
    //         wallL.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    //         wallR.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    //     } else {
    //         wallL.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    //         wallR.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    //     }
    //     currentPosition = Wall.position(degrees); // Update position
    // }
    // wallL.stop();
    // wallR.stop();
}

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(6, 10, 0, 40, 0); // first val can be 10 or 12
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(8, .4, 0, 2.5, 0); // 0.009, 15
  chassis.set_swing_constants(12, .3, 0, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 200, 5000);
  chassis.set_turn_exit_conditions(2.0, 300, 3000);
  chassis.set_swing_exit_conditions(2.0, 300, 3000);
}

/**
 * Sets constants to be more effective for odom movements.
 * For functions like drive_to_point(), it's often better to have
 * a slower max_voltage and greater settle_error than you would otherwise.
 */

void odom_constants(){
  default_constants();
  chassis.heading_max_voltage = 10;
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
  chassis.boomerang_lead = .5;
  chassis.drive_min_voltage = 0;
}

/**
 * The expected behavior is to return to the start position.
 */

/*
AUTONS

solo AWP - red & blue
5 ring - red & blue
goal rush - red & blue

win point goal side - red & blue
win point ring side - red & blue
*/

/*
ARCHIVES 


  2 RING AUTON
  chassis.set_drive_constants(6, 3, 0.01, 0, 0);
  chassis.drive_distance(-5.7);
  Clamp.set(1);
  task::sleep(300);
  intake.spin(fwd, 12, volt);
  task::sleep(300);
  chassis.set_drive_constants(8, 3, 0.01, 0, 0);
  chassis.turn_to_angle(-60); // -110
  chassis.drive_distance(4.3);
  chassis.drive_distance(-2);
  chassis.turn_to_angle(0);
  chassis.drive_distance(4.3);
  chassis.turn_to_angle(110);
  task::sleep(2000);
  chassis.drive_distance(20);

  OLD GOAL RUSH
    // chassis.drive_distance(-14);
  // chassis.left_swing_to_angle(-30);
  // //chassis.turn_to_angle(-30); // chassis.turn_to_angle(-30);
  // //chassis.drive_distance(-1.6); // approach first goal
  // Clamp.set(true); //clamp
  // task::sleep(300);
  // intake.spin(forward, 12, volt);
  // chassis.drive_distance(1.5);
  // intake.stop();
  // chassis.turn_to_angle(0);
  // chassis.drive_distance(6);
  // chassis.turn_to_angle(-180);
  // Clamp.set(false); // set down first goal
  // chassis.drive_distance(4);// approach auton line
  // chassis.set_drive_constants(4.0, 12, 0, 1, 0);
  // chassis.turn_to_angle(-120);
  // intake.spin(forward, 12, volt);
  // chassis.drive_distance(3);
  // chassis.set_drive_constants(12.0, 12, 0, 1, 0); 
  // intake.stop();
  // chassis.drive_distance(1); // approach second goal
  // chassis.turn_to_angle(-90);
  // chassis.set_drive_constants(6.0, 12, 0, 1, 0); 
  // chassis.drive_distance(-4);
  // Clamp.set(true);
  // chassis.set_drive_constants(12.0, 12, 0, 1, 0); 
  // intake.spin(forward, 12, volt);
  // chassis.turn_to_angle(-45);
  // chassis.drive_distance(-6);
  // Doink.set(true);
  // chassis.drive_distance(-2);
  // chassis.turn_to_angle(-135);

  AWP BLUE - COLLECT 2 STACK AND GO TO LADDER, 2 STAKES
  // chassis.set_drive_constants(4.0, 12, 0, 1, 0);
  // intakeArm.set(true);
  // chassis.drive_distance(-2.7); // appraoch 2 stack
  // intakeArm.set(false);
  // intake.spin(forward, 12, volt);
  // chassis.drive_stop(brake);
  // task::sleep(500);
  // intake.stop();
  // chassis.turn_to_angle(-65); // align with alliance stake
  // chassis.set_drive_constants(12.0, 12, 0, 1, 0);
  // chassis.drive_distance(1.82); // drive to alliance stake
  // intake.spin(forward, 12, volt); // score on alliance stake
  // task::sleep(750);
  // intake.stop();
  // chassis.turn_to_angle(-105); // face ring
  // intake.spin(forward, 12, volt);
  // chassis.drive_distance(-3); // pick up
  // task::sleep(100);
  // // task::sleep(500);
  // intake.stop();
  // chassis.turn_to_angle(-270); // face mogo
  // chassis.set_drive_constants(6, 12, 0, 1, 0);
  // chassis.drive_distance(4);
  // Clamp.set(true); // clamp on mogo
  // chassis.set_drive_constants(12.0, 12, 0, 1, 0);
  // //task::sleep(100);
  // chassis.turn_to_angle(-165); // face rings
  // intake.spin(forward, 12, volt);
  // chassis.set_drive_constants(5.0, 12, 0, 1, 0);
  // chassis.drive_distance(-3);
  // intake.stop();
  // chassis.drive_distance(-1);
  // chassis.turn_to_angle(30); // face ladder
  // intake.spin(forward, 12, volt);
  // chassis.set_drive_constants(8.0, 12, 0, 1, 0);
  // chassis.drive_distance(-8);
  // intake.stop();
  // chassis.drive_stop(brake);

  AWP RED
    // TEMP NOT IN USE
    // chassis.drive_distance(-2.1);
    // chassis.turn_to_angle(90);
    // chassis.drive_distance(-2);
    // intake.spin(fwd, 12, volt);
    // task::sleep(300);
    // chassis.right_swing_to_angle(135);
    // chassis.drive_distance(7);
    // intake.stop();
    // chassis.turn_to_angle(180);
    // chassis.drive_distance(-3);
    // Clamp.set(1);
    // intake.spin(fwd, 12, volt);
    // intake.stop();
    // chassis.turn_to_angle(135);
    // chassis.drive_distance(-4);
    // Clamp.set(0);
    // chassis.turn_to_angle(-135);
    // chassis.drive_distance(-7);
    // Clamp.set(1);
    // chassis.turn_to_angle(0);
    // intake.spin(fwd, 12, volt);
    // chassis.drive_distance(3);

    // OLD CODE
    // chassis.set_drive_constants(4.0, 12, 0, 1, 0);
    // intakeArm.set(true);
    // chassis.drive_distance(-2.7); // appraoch 2 stack
    // intakeArm.set(false);
    // intake.spin(forward, 12, volt);
    // chassis.drive_stop(brake);
    // task::sleep(500);
    // intake.stop();
    // chassis.turn_to_angle(65); // align with alliance stake
    // chassis.set_drive_constants(12.0, 12, 0, 1, 0);
    // chassis.drive_distance(1.82); // drive to alliance stake
    // intake.spin(forward, 12, volt); // score on alliance stake
    // task::sleep(750);
    // intake.stop();
    // chassis.turn_to_angle(105); // face ring
    // intake.spin(forward, 12, volt);
    // chassis.drive_distance(-3); // pick up
    // task::sleep(100);
    // // task::sleep(500);
    // intake.stop();
    // chassis.turn_to_angle(270); // face mogo
    // chassis.set_drive_constants(6, 12, 0, 1, 0);
    // chassis.drive_distance(4);
    // Clamp.set(true); // clamp on mogo
    // chassis.set_drive_constants(12.0, 12, 0, 1, 0);
    // //task::sleep(100);
    // chassis.turn_to_angle(165); // face rings
    // intake.spin(forward, 12, volt);
    // chassis.set_drive_constants(5.0, 12, 0, 1, 0);
    // chassis.drive_distance(-3);
    // intake.stop();
    // chassis.drive_distance(-1);
    // chassis.turn_to_angle(-30); // face ladder
    // intake.spin(forward, 12, volt);
    // chassis.set_drive_constants(8.0, 12, 0, 1, 0);
    // chassis.drive_distance(-8);
    // intake.stop();
    // chassis.drive_stop(brake);

    SOLO AWP B
     // score 1 ring, touch ladder
    chassis.set_drive_constants(6, 3, 0.01, 0, 0); 
    chassis.set_turn_exit_conditions(2.0, 300, 500);
    chassis.drive_distance(-4);
    chassis.drive_distance(1.8);
    chassis.turn_to_angle(90);
    chassis.drive_distance(-2.4);
    task::sleep(500);
    intake.spin(fwd, 12, volt);
    task::sleep(500);
    chassis.drive_distance(2.5);
    chassis.turn_to_angle(220);
    chassis.drive_distance(-8);
    Clamp.set(1);
    task::sleep(500);
    chassis.turn_to_angle(-7);
    task::sleep(500);
    chassis.drive_distance(5.5);
    intake.spin(fwd, 12, volt);
    task::sleep(500);
    chassis.turn_to_angle(185);
    task::sleep(300);
    chassis.drive_distance(5);
    intake.stop();

    SOLO AWP R
  move back
  face 90
  move back
  spin intake
  swing to 135 (rollers face ring)
  drive forward
  stop intake
  face 180
  move back
  clamp
  spin intake
  stop intake
  face 135
  move back
  release clamp
  face -135
  move back
  clamp
  face 0
  spin intake
  move forward
  // score 1 ring, touch ladder
  chassis.set_drive_constants(6, 3, 0.01, 0, 0); 
  chassis.drive_distance(-4);
  chassis.drive_distance(2);
  chassis.turn_to_angle(-90);
  chassis.drive_distance(-2.4);
  task::sleep(500);
  intake.spin(fwd, 12, volt);
  task::sleep(500);
  chassis.drive_distance(1);
  chassis.turn_to_angle(-240);
  intake.stop();
  chassis.drive_distance(-8);
  Clamp.set(1);
  task::sleep(500);
  chassis.turn_to_angle(0);
  chassis.drive_distance(5.5);
  intake.spin(fwd, 12, volt);
  chassis.turn_to_angle(-170);
  chassis.drive_distance(10);
  intake.stop();
*/

void auto_colsort() {
  int TARGET_HUE = 20;
  int TOLERANCE = 10;
  intake.spin(fwd, 12, volt);

  // COLOUR SORTING
  // Turn on the sensor's LED for better detection
  ColSort.setLight(ledState::on);

  // Get the hue value of the detected color
  int detectedHue = ColSort.hue();
  if (detectedHue >= TARGET_HUE - TOLERANCE && detectedHue <= TARGET_HUE + TOLERANCE) {
    // Action for red object (e.g., spin intake to collect)
    task::sleep(50);
    intake.stop();
    task::sleep(50);
  }
}

void five_b() {
  /*
  // FINALS 3 11:04:10
  drive forward
  face wall stake
  lb spin
  face 2 stack
  spin intake
  drive forward
  face mogo (should be 90 degree)
  face 4 stack
  drive forward
  face other part of 4 stack
  drive forward
  drive back
  face corner stack
  doink set true
  face positive corner
  drive forward
  */

  // 5 ring
  chassis.set_drive_constants(6, 3, 0.01, 0, 0);
  chassis.drive_distance(-5.7);
  Clamp.set(1);
  task::sleep(250);
  intake.spin(fwd, 12, volt);
  task::sleep(250);
  chassis.turn_to_angle(-135);
  chassis.drive_distance(3.5);
  chassis.drive_distance(-2);
  chassis.turn_to_angle(-105); // face 2nd 2 stak
  chassis.drive_distance(4.5);
  chassis.drive_distance(-4);
  task::sleep(250);
  chassis.turn_to_angle(-60);
  chassis.drive_distance(3);
  intake.stop();
  chassis.drive_distance(2);
  chassis.drive_distance(-2);
  intake.spin(fwd, 12, volt);
  chassis.turn_to_angle(-25);
  chassis.drive_distance(8.5);// drive to 4 stack
  task::sleep(1000);
  chassis.drive_distance(-2);
  //Redirect.set(1);
  chassis.turn_to_angle(-90);
  chassis.drive_distance(-17);
}

void five_r() {
  /*
  // FINALS 3 11:04:10
  drive straight
  clamp
  face 2 ring
  pick up 1 ring
  move back
  face 1 ring
  drive to 1ring
  pick up
  turn to face 2ring
  drive to 2ring
  pick up 2nd ring from 2ring

  drive forward
  clamp
  spin intake
  face -150
  drive forward
  drive back same amount
  face -60
  drive forward
  face -150
  drive forward
  drive back
  */
  chassis.set_drive_constants(6, 3, 0.01, 0, 0);
  chassis.drive_distance(-5.7);
  Clamp.set(1);
  task::sleep(250);
  intake.spin(fwd, 12, volt);
  task::sleep(250);
  chassis.turn_to_angle(135);
  chassis.drive_distance(3.5);
  chassis.drive_distance(-2);
  chassis.turn_to_angle(105); // face 2nd 2 stak
  chassis.drive_distance(4.5);
  chassis.drive_distance(-2);
  task::sleep(250);
  chassis.turn_to_angle(60);
  chassis.drive_distance(3);
  intake.stop();
  chassis.drive_distance(2);
  chassis.drive_distance(-2);
  intake.spin(fwd, 12, volt);
  chassis.turn_to_angle(25);
  chassis.drive_distance(8.5);// drive to 4 stack
  task::sleep(1000);
  chassis.drive_distance(-2);
  //Redirect.set(1);
  chassis.turn_to_angle(90);
  chassis.drive_distance(-17);
}

void five_b_wall() {
  // score wall stake first
  chassis.drive_distance(8.5, chassis.get_absolute_heading(), 6);
  chassis.turn_to_angle(45); // face wall stake
  wallL.setVelocity(100, pct);
  chassis.drive_distance(-1);
  chassis.turn_to_angle(-150); // face 2 stack next to mogo
  intake.spin(fwd, 12, volt);
  chassis.drive_distance(3);
  chassis.turn_to_angle(90); // face mogo
  chassis.drive_distance(-5, chassis.get_absolute_heading(), 8);
  Clamp.set(1);
  chassis.turn_to_angle(45); // 4 stack 1
  chassis.drive_distance(5);
  chassis.turn_to_angle(80); // 4 stack 2
  chassis.drive_distance(3);
  chassis.drive_distance(-3.5);
  chassis.turn_to_angle(150); // 4 stack (negative corner)
  chassis.drive_distance(7.5);
  Doink.set(true);
  chassis.turn_to_angle(-90); // face positive corner
  chassis.drive_distance(8);
  chassis.drive_stop(vex::brake);
}

void grush_r() {
  // FINALS 3 11:04:10
  Doink.set(1);
  fIntake.spin(fwd, 12, volt);
  chassis.drive_distance(6, chassis.get_absolute_heading(), 12, 12, 1.5, 200, 5000, 4, 0, 50, 0, 0, 0, 0, 0);
  task::sleep(10);
  Doink.set(0); // grab mogo
  task::sleep(250);
  hIntake.spin(fwd, 7, volt);
  chassis.drive_distance(-3, chassis.get_absolute_heading(), 12, 12, 1.5, 200, 5000, 4, 0, 50, 0, 0, 0, 0, 0);
  hIntake.stop();
  fIntake.stop();

  intake.spin(fwd, 12, volt);
  task::sleep(200); // TUNE THIS
  intake.stop();

  Doink.set(1);
  task::sleep(10);
  chassis.drive_distance(1);
  chassis.set_drive_constants(6, 20, 0, 20, 0); // first val can be 10 or 12
  chassis.drive_distance(-1, chassis.get_absolute_heading(), 6, 6, 1.5, 200, 1000);
  chassis.set_drive_constants(6, 10, 0, 40, 0); // first val can be 10 or 12
  Doink.set(0);
  task::sleep(200);
  // chassis.turn_to_angle(180, 8, 2.0, 300, 1000); // face mogo 1 for clamp
  // chassis.drive_distance(-5.3);
  // Clamp.set(1); // CLAMP FIRST MOGO
  // task::sleep(700);
  // intake.spin(fwd, 12, volt);
  // task::sleep(500);
  // intake.stop();
  // Clamp.set(0);

/*
  chassis.set_turn_constants(8, .4, 0, 2.5, 0); // 0.009, 15
  chassis.set_swing_constants(12, .3, 0, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 200, 5000);
  chassis.set_turn_exit_conditions(2.0, 300, 3000);
*/

  chassis.turn_to_angle(140, 8, 2.0, 300, 1000);
  chassis.drive_distance(-6);
  Clamp.set(1); // CLAMP MIDDLE MOGO
  intake.spin(fwd, 12, volt);
  task::sleep(300);

  chassis.turn_to_angle(165); // INITIALL 105  --------
  // TURN ON COLOUR SORTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
  Doink.set(true); // go to corner
  chassis.drive_distance(7);
  chassis.turn_to_angle(-180);
  chassis.turn_to_angle(75);
  Clamp.set(false);
  Doink.set(false);
  chassis.turn_to_angle(-15);
  chassis.drive_distance(7);
  // intake.spin(directionType::rev, 12, volt);
  // task::sleep(700);
  // intake.spin(fwd, 12, volt);
  // task::sleep(700);
  // intake.spin(directionType::rev, 12, volt);
  // task::sleep(700);
  // intake.spin(fwd, 12, volt);
  // task::sleep(700);
  // intake.spin(directionType::rev, 12, volt);
  // task::sleep(700);
  // intake.spin(fwd, 12, volt);
  // task::sleep(700);


  // chassis.drive_distance(-4);
  // Claw.set(true); // drop mogo
  // chassis.drive_distance(-1);
  // chassis.turn_to_angle(-180);
  // task::sleep(250);
  // chassis.drive_distance(-3);
  // Clamp.set(true);
  // intake.spin(fwd, 12, volt);
  // task::sleep(500);
  // chassis.turn_to_angle(0); // knocked rings
  // Clamp.set(false);
  // chassis.drive_distance(5);
  // task::sleep(500);
  // intake.stop();
  // chassis.turn_to_angle(105); // other mogo
  // chassis.drive_distance(-5, chassis.get_absolute_heading(), 6);
  // Clamp.set(true);
  // task::sleep(250);
  // intake.spin(fwd, 12, volt);
  // chassis.turn_to_angle(150);
  // chassis.drive_distance(8, chassis.get_absolute_heading(), 5);

  // // corner
  // task::sleep(500);
  // chassis.drive_distance(-2);
  // chassis.drive_distance(2); // picking up  opp ring
  // task::sleep(500);
  // chassis.drive_distance(-2);
  // chassis.turn_to_angle(-30);
  // intake.spin(directionType::rev, 12, volt); // spit it out
  // task::sleep(500);
  // chassis.turn_to_angle(150);
  // chassis.drive_distance(2); // 3rd ring
  // task::sleep(500);
  // chassis.drive_distance(-5);
  // chassis.right_swing_to_angle(-60);
   
  /*
  initial -15
  drive forward
  grab goal
  drive back
  face wall 30
  let go of doink and claw
  face mogo (back faces wall) -150
  move back
  clamp
  spin intake
  unclamp
  face knocked ring 0
  drive forward & pickup
  stop intake
  face mogo 90
  mvoe back
  clamp
  face corner 150
  drive forward
  pick up 1st
  spit 2nd
  pick up 3rd
  move back
  right swing backwards to -90

  */

  // drive straight then score some mogos
  // chassis.turn_to_angle(120); // face other mogo
  // chassis.drive_distance(-2.5);
  // Clamp.set(true); // clamp first mogo
  // task::sleep(250);
  // intake.spin(fwd, 12, volt);
  // chassis.turn_to_angle(30);
  // Clamp.set(false);
  // chassis.turn_to_angle(-120); // face middle goal
  // chassis.drive_distance(-6); // go to middle goal
  // Clamp.set(true); // clamp middle goal
  // chassis.turn_to_angle(165); // face corner stack
  // chassis.drive_distance(12, chassis.get_absolute_heading(), 6, 6, 1.5, 200, 5000, 4, 0, 100, 0, 0, 0, 0, 0);
  // task::sleep(500); // red ring
  // chassis.drive_distance(-2, chassis.get_absolute_heading(), 6);
  // chassis.drive_distance(2, chassis.get_absolute_heading(), 6);
  // task::sleep(500); // blue ring
  // chassis.drive_distance(-2, chassis.get_absolute_heading(), 6);
  // chassis.turn_to_angle(255);
  // intake.spin(directionType::rev, 12, volt); // spit it out
  // task::sleep(500);
  // chassis.turn_to_angle(165);
  // chassis.drive_distance(2);
  // chassis.drive_distance(-2);
  // Doink.set(true);
  // task::sleep(250);
  // chassis.turn_to_angle(0);
  // chassis.drive_distance(3);
  // chassis.drive_stop(brake);
  
}

void grush_r2() {
  // FINALS 3 11:04:10
  // score on middle stake with lb
  wallL.setVelocity(80, pct);
  wallR.setVelocity(80, pct);

  chassis.drive_distance(8.75, chassis.get_absolute_heading(), 12, 12, 1.5, 200, 5000, 4, 0, 100, 0, 0, 0, 0, 0);
  chassis.turn_to_angle(60, 8, 2, 300, 500);
  ladyBrown(-480);
  wallL.spinTo(-180, deg, false);
  wallR.spinTo(-180, deg, false);
  chassis.drive_distance(-4);
  Clamp.set(true);
  task::sleep(250);
  chassis.turn_to_angle(90);
  intake.spin(fwd, 12, volt);
  chassis.drive_distance(4);
  chassis.turn_to_angle(135);
  chassis.drive_distance(8);
  task::sleep(1000);
  chassis.drive_distance(-2);
}

void grush_b() {
  // FINALS 3 11:04:10
  Doink.set(1);
  fIntake.spin(fwd, 12, volt);
  hIntake.spin(fwd, 5, volt);
  chassis.drive_distance(6, chassis.get_absolute_heading(), 12, 12, 1.5, 200, 5000, 4, 0, 50, 0, 0, 0, 0, 0);
  hIntake.stop();
  Doink.set(0); // grab mogo
  task::sleep(10);  
  chassis.drive_distance(-3.5, chassis.get_absolute_heading(), 12, 12, 1.5, 200, 5000, 4, 0, 50, 0, 0, 0, 0, 0);
  fIntake.stop();

  intake.spin(fwd, 12, volt);
  task::sleep(200);                                                                                                                  
  
 
  intake.stop();

  Doink.set(1);
  task::sleep(10);
  chassis.drive_distance(1);
  chassis.drive_distance(-1.5);
  Doink.set(0);
  
  // CLAMP FIRST MOGO
  // chassis.turn_to_angle(190, 8, 2.0, 300, 1000); // face mogo 1 for clamp
  // chassis.drive_distance(-5.3);
  // Clamp.set(1); // CLAMP FIRST MOGO
  // task::sleep(700);
  // intake.spin(fwd, 12, volt);
  // task::sleep(500);
  // intake.stop();
  // chassis.drive_distance(2);
  // chassis.turn_to_angle(90, 8, 2.0, 300, 1000);
  // Clamp.set(0);

/*
  chassis.set_turn_constants(8, .4, 0, 2.5, 0); // 0.009, 15
  chassis.set_swing_constants(12, .3, 0, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 200, 5000);
  chassis.set_turn_exit_conditions(2.0, 300, 3000);
*/

  chassis.turn_to_angle(-127, 8, 2.0, 300, 2000);
  chassis.drive_distance(-3.5);
  task::sleep(200);  
  Clamp.set(1); // CLAMP MIDDLE MOGO
  task::sleep(500);  
  intake.spin(fwd, 12, volt);
  task::sleep(700);

  chassis.turn_to_angle(-120, 8, 2.0, 300, 1000); // INITIALL 105  --------
  // TURN ON COLOUR SORTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
  Doink.set(true); // go to corner
  intake.stop();
  chassis.drive_distance(9);
  chassis.turn_to_angle(180, 8, 2.0, 300, 1000);
  chassis.turn_to_angle(75);
  Clamp.set(false);
  Doink.set(false);
  chassis.drive_distance(8);

  // intake.spin(directionType::rev, 12, volt);
  // task::sleep(700);
  // intake.spin(fwd, 12, volt);
  // task::sleep(700);
  // intake.spin(directionType::rev, 12, volt);
  // task::sleep(700);
  // intake.spin(fwd, 12, volt);
  // task::sleep(700);
  // intake.spin(directionType::rev, 12, volt);
  // task::sleep(700);
  // intake.spin(fwd, 12, volt);
  // task::sleep(700);

  
}

void gdisrupt_r() {
  Doink.set(true);
  chassis.drive_distance(7.5, chassis.get_absolute_heading(), 8);
  task::sleep(100);
  chassis.turn_to_angle(90);
  chassis.drive_distance(2, chassis.get_absolute_heading(), 6);
  Doink.set(false);
  task::sleep(250);
  chassis.drive_distance(-4, chassis.get_absolute_heading(), 6);
  chassis.turn_to_angle(45);
  chassis.drive_distance(-3, chassis.get_absolute_heading(), 6);
  Clamp.set(true);
  task::sleep(250);
  chassis.turn_to_angle(90);
  intake.spin(fwd, 12, volt);
  chassis.drive_distance(4);
  task::sleep(1500);
  chassis.turn_to_angle(-90);
  Clamp.set(false);
  chassis.turn_to_angle(0);
  //chassis.drive_distance(-3, chassis.get_absolute_heading(), 6);
  //chassis.drive_distance(4);
 
  // //Doink.set(true);
  // chassis.drive_distance(8.3, chassis.get_absolute_heading(), 12);
  // //chassis.drive_side_distance(8.3, 10, 12, 0, 200, 0, 12, 0, 200, 0);
  // //chassis.drive_distance(8.3, chassis.get_absolute_heading(), 10, 12, 1.5, 200, 5000, 12, 0, 200, 0, 0, 0, 0, 0);
  // chassis.turn_to_angle(90);
  // Doink.set(false);
  // task::sleep(250);
  // chassis.turn_to_angle(50);
  // chassis.drive_distance(-3, chassis.get_absolute_heading(), 6);
  // Clamp.set(true);
  // task::sleep(250);
  // intake.spin(fwd, 12, volt);
  // task::sleep(500);
  // chassis.turn_to_angle(80);
  // chassis.drive_distance(6, chassis.get_absolute_heading(), 6);
  // intake.spin(fwd, 12, volt);
  // chassis.drive_stop(brake);
}

void gdisrupt_b() {
  Doink.set(true);
  chassis.drive_distance(7.5, chassis.get_absolute_heading(), 8);
  task::sleep(100);
  chassis.turn_to_angle(90);
  chassis.drive_distance(2, chassis.get_absolute_heading(), 6);
  Doink.set(false);
  task::sleep(250);
  //chassis.drive_distance(-4, chassis.get_absolute_heading(), 6);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-3, chassis.get_absolute_heading(), 6);
  Clamp.set(true);
  task::sleep(250);
  chassis.turn_to_angle(-90);
  intake.spin(fwd, 12, volt);
  chassis.drive_distance(4);
  task::sleep(500);
  chassis.turn_to_angle(90);
  //Clamp.set(false);
  chassis.turn_to_angle(0);
  //chassis.drive_distance(-3, chassis.get_absolute_heading(), 6);
  //chassis.drive_distance(4);
}

void awp_solo_b() {
  chassis.drive_distance(-4, chassis.get_absolute_heading(), 6);
  Clamp.set(true);
  fIntake.spin(fwd,12, volt);
  hIntake.spin(fwd,5,volt);
  task::sleep(1000);
  chassis.turn_to_angle(180);
  chassis.drive_distance(2);
}

void awp_solo_r() {
  /*
  START ON RING (NEGATIVE) SIDE BLUE
  drive forward
  face -45
  spin lady brown, score alliance stake
  drive back
  clamp mogo
  wait
  spin intake
  face 135
  drive forward (pick up 1st ring)
  face 170
  drive forward (pick up 2nd ring)
  drive back
  face -135
  drive fowrard (pick up 3rd ring)
  face -45
  drive forward
  face 0 (face 2 stack)
  drop mogo
  drive forward
  stop intake when it picks up blue ring, keep driving forward
  face -120
  drive back
  clamp mogo
  wait
  spin intake
  drive back
  face 0
  drive forward
  drive back
  face 135
  drive forward (stop at ladder)
  */
  chassis.set_drive_constants(9, 8, 0, 100, 0); 
  wallL.setVelocity(75, pct);
  wallR.setVelocity(75, pct);

  chassis.turn_to_angle(47);
  chassis.drive_distance(0.4, chassis.get_absolute_heading(), 6, 6, 1.5, 200, 5000, 15, 0, 40, 0, .4, 0, 1, 0);
  wallL.spinTo(-570, deg, false);
  wallR.spinTo(-570, deg, false);
  task::sleep(700);

  chassis.drive_distance(-2.9); // -2.9
  wallL.spinTo(-300, deg, false);
  wallR.spinTo(-300, deg, false);
  chassis.turn_to_angle(90);
  chassis.drive_distance(-3, chassis.get_absolute_heading(), 6); // mogo
  Clamp.set(1);
  task::sleep(250);
  intake.spin(fwd, 12, volt);
  chassis.turn_to_angle(-180); // 2 stack
  chassis.drive_distance(3.5);
  chassis.turn_to_angle(45);

  // 3 ring for riverbots
  chassis.drive_distance(5.2); //
  chassis.turn_to_angle(0); // 2 stack near alliance
  Clamp.set(false);
  chassis.drive_distance(7, chassis.get_absolute_heading(), 5);
  chassis.turn_to_angle(90);
  intake.stop();
  chassis.drive_distance(-4.3);
  Clamp.set(true); // mogo
  task::sleep(250);
  chassis.turn_to_angle(0);
  intake.spin(fwd, 12, volt);
  chassis.drive_distance(4, chassis.get_absolute_heading(), 6);
  //chassis.drive_distance(-2);
  chassis.turn_to_angle(-180);
  chassis.drive_distance(8, chassis.get_absolute_heading(), 10, 10, 1.5, 200, 5000, 8, 0, 80, 0, .4, 0, 1, 0);
}

void awp_goal_b() {
  chassis.drive_distance(-4.3);
  Clamp.set(1);
  task::sleep(500);
  intake.spin(fwd, 12, volt);
  chassis.turn_to_angle(90);
  chassis.drive_distance(4.5);
  chassis.turn_to_angle(-90);
  chassis.drive_distance(9);
  
}

void awp_goal_r() {
  // Q122, day 2 2:15:36
  chassis.drive_distance(-4.3);
  Clamp.set(1);
  task::sleep(500);
  intake.spin(fwd, 12, volt);
  chassis.turn_to_angle(-90);
  chassis.drive_distance(4.5);
  chassis.turn_to_angle(90);
  chassis.drive_distance(2, chassis.get_absolute_heading(), 4);
  
}

void awp_ring_r() {
  // Q122, day 2 2:15:36
  // 5 ring with alliance stake
  chassis.set_drive_constants(6, 8, 0, 40, 0); 
  wallL.setVelocity(75, pct);
  wallR.setVelocity(75, pct);

  //chassis.turn_to_angle(47);
 // chassis.drive_distance(0.4, chassis.get_absolute_heading(), 6, 6, 1.5, 200, 5000, 15, 0, 40, 0, .4, 0, 1, 0);
  wallL.spinTo(-570, deg, false);
  wallR.spinTo(-570, deg, false);
  task::sleep(700);

  chassis.drive_distance(-2.3); // -2.9
  wallL.spinTo(-300, deg, false);
  wallR.spinTo(-300, deg, false);
  chassis.turn_to_angle(45);
  chassis.drive_distance(-4.5, chassis.get_absolute_heading(), 6); // mogo, -4.5
  Clamp.set(1);
  task::sleep(250);
  intake.spin(fwd, 12, volt);

  chassis.turn_to_angle(-175); // 1st 2 stack
  chassis.drive_distance(3.5);
  task::sleep(500);
  chassis.drive_distance(-2);
  chassis.turn_to_angle(-190); // face 2nd 2 stak
  chassis.drive_distance(3.2);
  task::sleep(250);
  chassis.drive_distance(-2);
  task::sleep(250);
  chassis.turn_to_angle(95);
  chassis.drive_distance(3); // 2 stack to the left of mogo
  intake.stop();
  chassis.turn_to_angle(-75); // ladder
  intake.spin(fwd, 12, volt);
  chassis.drive_distance(6);
  intake.stop();
}

void awp_ring_b() {
  // 2 ring for local
  /*
  START ON RING (NEGATIVE) SIDE BLUE
  drive forward
  face -45
  spin lady brown, score alliance stake
  drive back
  clamp mogo
  wait
  spin intake
  face 135
  drive forward (pick up 1st ring)
  face 170
  drive forward (pick up 2nd ring)
  drive back
  face -135
  drive fowrard (pick up 3rd ring)
  face -45
  drive forward
  face 0 (face 2 stack)
  drop mogo
  drive forward
  stop intake when it picks up blue ring, keep driving forward
  face -120
  drive back
  clamp mogo
  wait
  spin intake
  drive back
  face 0
  drive forward
  drive back
  face 135
  drive forward (stop at ladder)
  */
 // Q122, day 2 2:15:36
  // 5 ring with alliance stake
  chassis.set_drive_constants(6, 8, 0, 40, 0); 
  wallL.setVelocity(75, pct);
  wallR.setVelocity(75, pct);

  //chassis.turn_to_angle(47);
 // chassis.drive_distance(0.4, chassis.get_absolute_heading(), 6, 6, 1.5, 200, 5000, 15, 0, 40, 0, .4, 0, 1, 0);
  wallL.spinTo(-570, deg, false);
  wallR.spinTo(-570, deg, false);
  task::sleep(700);

  chassis.drive_distance(-2.3); // -2.9
  wallL.spinTo(-300, deg, false);
  wallR.spinTo(-300, deg, false);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-4.5, chassis.get_absolute_heading(), 6); // mogo, -4.5
  Clamp.set(1);
  task::sleep(250);
  intake.spin(fwd, 12, volt);

  chassis.turn_to_angle(175); // 1st 2 stack
  chassis.drive_distance(3.5);
  task::sleep(500);
  chassis.drive_distance(-2);
  chassis.turn_to_angle(190); // face 2nd 2 stak
  chassis.drive_distance(3.2);
  task::sleep(250);
  chassis.drive_distance(-2);
  task::sleep(250);
  chassis.turn_to_angle(-95);
  chassis.drive_distance(3); // 2 stack to the left of mogo
  intake.stop();
  chassis.turn_to_angle(75); // ladder
  intake.spin(fwd, 12, volt);
  chassis.drive_distance(6);
  intake.stop();

 // dumbass code #1
  // Q122, day 2 2:15:36
  // 5 ring with alliance stake
  // chassis.set_drive_constants(6, 8, 0, 40, 0); 
  // wallL.setVelocity(75, pct);
  // wallR.setVelocity(75, pct);

  // chassis.turn_to_angle(-47);
  // chassis.drive_distance(0.4, chassis.get_absolute_heading(), 6, 6, 1.5, 200, 5000, 15, 0, 40, 0, .4, 0, 1, 0);
  // wallL.spinTo(-570, deg, false);
  // wallR.spinTo(-570, deg, false);
  // task::sleep(700);

  // chassis.drive_distance(-3.1); // -2.9
  // wallL.spinTo(-300, deg, false);
  // wallR.spinTo(-300, deg, false);
  // chassis.turn_to_angle(-90);
  // chassis.drive_distance(-4.5, chassis.get_absolute_heading(), 6); // mogo
  // Clamp.set(1);
  // task::sleep(250);
  // intake.spin(fwd, 12, volt);

  // chassis.turn_to_angle(165); // 1st 2 stack
  // chassis.drive_distance(3.5);
  // task::sleep(250);
  // chassis.drive_distance(-2);
  // chassis.turn_to_angle(175); // face 2nd 2 stak
  // chassis.drive_distance(3.7);
  // task::sleep(250);
  // chassis.drive_distance(-2);
  // task::sleep(250);
  // chassis.turn_to_angle(-120);
  // chassis.drive_distance(3); // 2 stack to the left of mogo
  // intake.stop();
  // chassis.turn_to_angle(30); // ladder
  // intake.spin(fwd, 12, volt);
  // chassis.drive_distance(8);
  // intake.stop();

  // dumbass code #2
  //chassis.drive_distance(1, chassis.get_absolute_heading(), 7);
  // chassis.drive_distance(0.5, chassis.get_absolute_heading(), 6, 6, 1.5, 200, 1000);
  // task::sleep(250);
  // ladyBrown(-200);
  // chassis.drive_distance(-3.5);
  // chassis.turn_to_angle(0-70);
  // chassis.drive_distance(-5);
  // Clamp.set(1);
  // task::sleep(250);
  // intake.spin(fwd, 12, volt);
  // task::sleep(250);
  // chassis.turn_to_angle(-205);
  // chassis.drive_distance(3.5);
  // chassis.drive_distance(-2);
  // chassis.turn_to_angle(-185); // face 2nd 2 stak
  // chassis.drive_distance(3.5);
  // chassis.drive_distance(-3);
  // task::sleep(250);
  // chassis.turn_to_angle(-130);
  // chassis.drive_distance(3);
  // intake.stop();
  // chassis.drive_distance(2);
  // chassis.drive_distance(-2);
  // intake.spin(fwd, 12, volt);
  // // 2 ring for local
  // chassis.turn_to_angle(40);
  // chassis.drive_distance(8);
  // chassis.drive_stop(brake);
}

void drive_test(){
  chassis.drive_distance(4.2);
  // chassis.drive_distance(8.4);
  // chassis.drive_distance(-4.2);
  // chassis.drive_distance(-8.4);
}

/**
 * The expected behavior is to return to the start angle, after making a complete turn.
 */

void turn_test(){
  // chassis.turn_to_angle(0);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(180);
  chassis.turn_to_angle(270);
  chassis.turn_to_angle(0);
}

/**
 * Should swing in a fun S shape.
 */

void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

/**
 * A little of this, a little of that; it should end roughly where it started.
 */

void full_test(){
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}

/**
 * Doesn't drive the robot, but just prints coordinates to the Brain screen 
 * so you can check if they are accurate to life. Push the robot around and
 * see if the coordinates increase like you'd expect.
 */

void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5,20, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(5,40, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}

/**
 * Should end in the same place it began, but the second movement
 * will be curved while the first is straight.
 */

void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}

/**
 * Drives in a square while making a full turn in the process. Should
 * end where it started.
 */

void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_pose(0, 18, 90);
  chassis.holonomic_drive_to_pose(18, 0, 180);
  chassis.holonomic_drive_to_pose(0, 18, 270);
  chassis.holonomic_drive_to_pose(0, 0, 0);
}