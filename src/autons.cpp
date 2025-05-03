#include "vex.h"

/**
 * Resets the constants for auton movement.
 * Modify these to change the default behavior of functions like
 * drive_distance(). For explanations of the difference between
 * drive, heading, turning, and swinging, as well as the PID and
 * exit conditions, check the docs.
 */

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, 0, 0, 0, 0);
  chassis.set_turn_constants(8, .4, 0.03, 3, 15);
  chassis.set_swing_constants(12, .3, 0, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 100, 5000);
  chassis.set_turn_exit_conditions(2.0, 200, 3000);
  chassis.set_swing_exit_conditions(2.0, 150, 3000);
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
void eight_r() {
  chassis.set_turn_constants(8, .8, 0.03, 6, 15);

  chassis.drive_distance(10);
  armToScorePos = true;
  task::sleep(400);
  
  chassis.drive_distance(-27, 0, 10, 0, 1.5, 100, 1500, 1.5, 0, 20, 0, 0, 0, 0, 0);
  chassis.drive_distance(-13, 0, 5, 0);
  armToScorePos = false;
  armToStartPos = true;
  Clamp.set(1);

  task::sleep(50);

  chassis.turn_to_angle(-101); // -105
  chassis.drive_distance(16);
  Doink.set(1);
  task::sleep(100);
  chassis.drive_distance(-24);
  
  convDir = FORWARD;
  chassis.set_turn_exit_conditions(2.0, 150, 3000);
  chassis.turn_to_angle(210);
  Doink.set(0);
  chassis.turn_to_angle(190);

  // the 3 rings
  chassis.drive_distance(12);
  chassis.right_swing_to_angle(115);
  chassis.drive_distance(10, chassis.get_absolute_heading(), 4);
  chassis.right_swing_to_angle(-45);
  chassis.drive_distance(12);

  armToStartPos = false;
  armToLoadPos = true;
  doAntiJam = false;

  chassis.turn_to_angle(165);
  task::sleep(15000);

  armToLoadPos = false;
  armToScorePos = true;

  chassis.drive_distance(10);
  convDir = STOP;

  //chassis.turn_to_angle(70);
  chassis.drive_distance(10, 0, 12);
  // rest is toilet mech
}

void five_r() {
  // 5 ring
  chassis.set_turn_constants(8, .8, 0.03, 6, 15);

  chassis.drive_distance(10);
  armToScorePos = true;
  task::sleep(400);
  
  chassis.drive_distance(-27, 0, 10, 0, 1.5, 100, 1500, 1.5, 0, 20, 0, 0, 0, 0, 0);
  chassis.drive_distance(-13, 0, 5, 0);
  armToScore = false;
  armToStartPos = true;
  Clamp.set(1);

  task::sleep(50);
  chassis.turn_to_angle(165);
  convDir = FORWARD;

  // the 3 rings
  chassis.drive_distance(23);
  chassis.right_swing_to_angle(120);
  chassis.drive_distance(10.5, chassis.get_absolute_heading(), 4);
  chassis.drive_distance(-4);
  chassis.turn_to_angle(22);
  chassis.drive_distance(25.5, 4);

  // chassis.drive_distance(-6);

  // get corner rings
  doAntiJam = false;
  chassis.turn_to_angle(68);
  chassis.drive_timeout = 600;
  chassis.drive_distance(26, chassis.get_absolute_heading(), 14);
  chassis.drive_timeout = 1200;
  chassis.drive_distance(16, chassis.get_absolute_heading(), 4);
  default_constants();
  task::sleep(500);
  chassis.drive_distance(-14, 65, 6);
  task::sleep(500);
  chassis.drive_distance(11, 65, 4);

  // get out
  armToStartPos = false;
  task::sleep(500);
  armToLoadPos = true;
  chassis.drive_distance(-60, 65);


}

void five_b() {
  // 5 ring
  chassis.set_turn_constants(8, .8, 0.03, 6, 15);

  chassis.drive_distance(10);
  armToScorePos = true;
  task::sleep(400);
  
  chassis.drive_distance(-27, 0, 10, 0, 1.5, 100, 5000, 1.5, 0, 20, 0, 0, 0, 0, 0);
  chassis.drive_distance(-13, 0, 5, 0);
  armToScore = false;
  armToStartPos = true;
  Clamp.set(1);
  task::sleep(50);

  // intake.spin(fwd, 12, volt);
  // task::sleep(250);
  // chassis.turn_to_angle(-135);
  // chassis.drive_distance(3.5);
  // chassis.drive_distance(-2);
  // chassis.turn_to_angle(-105); // face 2nd 2 stak
  // chassis.drive_distance(4.5);
  // chassis.drive_distance(-4);
  // task::sleep(250);
  // chassis.turn_to_angle(-60);
  // chassis.drive_distance(3);
  // intake.stop();
  // chassis.drive_distance(2);
  // chassis.drive_distance(-2);
  // intake.spin(fwd, 12, volt);
  // chassis.turn_to_angle(-25);
  // chassis.drive_distance(8.5);// drive to 4 stack
  // task::sleep(1000);
  // chassis.drive_distance(-2);
  // //Redirect.set(1);
  // chassis.turn_to_angle(-90);
  // chassis.drive_distance(-17);
}

void awp_solo_b() {
  // BARCBOTS 6 RING
  /*
  drive foward
  lb load
  spin intake
  face alliance stake
  lb score
  drive back
  clamp
  face auton rings
  drive foward
  face field wall
  drive forward
  face 2 stack
  drive forward
  face alliance stake
  drive forward
  face 2 stack (near alliacne stake)
  unclamp
  drive forward
  stop
  drive forward
  stop intake
  face mogo
  drive back
  clamp
  spin intake
  face 2 stack
  drive forward
  face ladder
  drive forward
  */
  wallL.setPosition(0, deg);
  wallL.setVelocity(100, pct);
  //chassis.set_turn_exit_conditions(2.0, 100, 3000);
  chassis.drive_distance(1.2, chassis.get_absolute_heading(), 6, 0, .05, 200, 500);

  wallL.spinTo(-240, deg, false);
  chassis.drive_distance(-4.7, chassis.get_absolute_heading(), 6, 0, 0.5, 200, 2000);
  Clamp.set(1);
  //task::sleep(250);

  //chassis.set_turn_exit_conditions(0.5, 300, 3000);
  chassis.turn_to_angle(200, 10, 2, 300, 1000, 0.35, 0.03, 3.4, 15);
  // spin intake
  //thread intake1(intakecontrol);
  chassis.drive_distance(1.2, chassis.get_absolute_heading(), 6, 0, .5, 200, 5000); // 1st stack
  task::sleep(100);
  chassis.drive_distance(-2.2, chassis.get_absolute_heading(), 6, 0, 0.2, 200, 2000); // 1.8, -3
  chassis.turn_to_angle(245);
  chassis.drive_distance(2); // second stack
  task::sleep(250);
  chassis.turn_to_angle(190);
  chassis.drive_distance(-2.4, chassis.get_absolute_heading(), 8, 0, 0.5, 200, 1000);
  Clamp.set(0);
  // do both of these lines to stop
  //intake1.interrupt();
  //intake.stop();

  chassis.turn_to_angle(65);
  //thread intake2(intakecontrol);
  chassis.drive_distance(7, chassis.get_absolute_heading(), 6, 0, 0.2, 200, 5000);
  //intake2.interrupt();
  intake.stop();
  task::sleep(200);

  //chassis.drive_distance(1, chassis.get_absolute_heading(), 6, 0, 0.05, 200, 5000);

  chassis.turn_to_angle(0); // FACE SECOND MOGO
  chassis.drive_distance(-2.9, chassis.get_absolute_heading(), 6, 0, 0.2, 100, 2000);
  Clamp.set(1);
  task::sleep(100);

  chassis.turn_to_angle(45);
  intake.spin(fwd, 12, volt);
  chassis.drive_distance(3, chassis.get_absolute_heading(), 8, 0, 0.2, 200, 1000, 10, 0, 80, 0, 0, 0, 0, 0);
  task::sleep(150);
  wallL.setBrake(brakeType::coast);
  chassis.drive_distance(-5, chassis.get_absolute_heading(), 12);
  intake.stop();
  //chassis.turn_to_angle(-150);
  //thread intakeTask(intakecontrol);
  wallL.spinTo(-200, deg); // touch ladder
}

void awp_solo_r() {
 
}

void awp_goal_b() {
  wallL.setPosition(0, deg);
  chassis.set_drive_constants(8, 10, 0, 100, 15);
  wallL.setVelocity(100, pct);
  wallL.spinTo(-240, deg);
  chassis.drive_distance(-3, chassis.get_absolute_heading(), 6);
  Clamp.set(1);
  task::sleep(500);
  chassis.turn_to_angle(180);
  intake.spin(fwd, 12, volt);
  task::sleep(500);
  chassis.turn_to_angle(0);
  
  chassis.drive_distance(-2, chassis.get_absolute_heading(), 6);
  wallL.spinTo(0, deg);
}

void gr_five() {
  chassis.set_turn_constants(8, .8, 0.03, 6, 15);

  chassis.drive_settle_error = 0.5;
  chassis.drive_distance(9);
  chassis.drive_settle_error = 1.5;
  armToScorePos = true;
  task::sleep(400);

  chassis.drive_distance(-40, 0, 6, 0, 1.5, 100, 2000, 1.5, 0, 22, 0, 0, 0, 0, 0);
  armToScore = false;
  armToStartPos = true;
  Clamp.set(1);
  task::sleep(50);
  chassis.turn_to_angle(115);
  chassis.drive_distance(14);
  DoinkR.set(1);
  task::sleep(100);
  chassis.drive_max_voltage = 6;
  chassis.drive_distance(8);
  chassis.turn_timeout = 350;
  chassis.turn_to_angle(130);
  chassis.turn_timeout = 2000;
  Doink.set(1);
  convDir = BACKWARD;

  chassis.drive_max_voltage = 10;
  chassis.drive_distance(-40);
  convDir = FORWARD;
  Doink.set(0);
  DoinkR.set(0);
  task::sleep(250);
  chassis.turn_to_angle(110);
  
  convDir = FORWARD;
  chassis.drive_min_voltage = 10;
  chassis.drive_distance(10); // 18
  chassis.drive_min_voltage = 0;
  // convDir = STOP;
  chassis.swing_timeout = 1000;
  chassis.left_swing_to_angle(240);
  convDir = FORWARD;
  chassis.drive_max_voltage = 6;
  chassis.drive_distance(34);

  convDir = STOP;
  chassis.turn_to_angle(-30);
  convDir = FORWARD;
  chassis.drive_max_voltage = 10;
  chassis.drive_distance(32); // 32

  chassis.drive_max_voltage = 4;
  chassis.drive_timeout = 750;
  chassis.turn_to_angle(-70);
  chassis.drive_timeout = 1000;
  // chassis.drive_distance(20);
  chassis.drive_side_distance(20, 8, 1.5, 0, 20, 0, 1.5, 0, 20, 0);

  chassis.drive_timeout = 2000;
  chassis.drive_max_voltage = 4;
  chassis.drive_distance(-14);
  task::sleep(250);
  chassis.drive_distance(12);

  DoinkR.set(true);
  chassis.drive_distance(-12);
  task::sleep(250);
  chassis.turn_to_angle(120);

  // chassis.turn_timeout = 1000;
  // chassis.turn_to_angle(175);

  // chassis.drive_max_voltage = 10;
  // chassis.drive_distance(35, 0, 10, 0, 1.5, 100, 900, 1.5, 0, 20, 0, 0, 0, 0, 0);
  // chassis.turn_timeout = 1300;
  // chassis.turn_to_angle(205);
  // armToLoadPos = false;
  // armToScore = true;
}

void grq_four() {
  chassis.set_drive_constants(8, 1.5, 0, 10, 0);
  chassis.set_turn_constants(8, .8, 0.03, 6, 15);

  chassis.drive_settle_error = 0.5;
  chassis.drive_distance(9);
  chassis.drive_settle_error = 1.5;
  armToScorePos = true;
  task::sleep(400);

  chassis.drive_distance(-22);
  armToScore = false;
  armToStartPos = true;
  chassis.turn_to_angle(30);
  DoinkR.set(1);
  task::sleep(250);
  chassis.turn_to_angle(0);

  chassis.drive_distance(-18, 0, 6, 0, 1.5, 100, 2000, 1.5, 0, 22, 0, 0, 0, 0, 0);

  Clamp.set(1);
  
  chassis.turn_to_angle(240, 6);
  chassis.turn_to_angle(215, 6);
  DoinkR.set(0);
  task::sleep(250);
  chassis.turn_to_angle(240);
  convDir = FORWARD;
  chassis.drive_max_voltage = 7;
  chassis.drive_distance(26);

  // convDir = STOP;
  chassis.turn_to_angle(-30);
  convDir = FORWARD;
  chassis.drive_max_voltage = 10;
  chassis.drive_distance(32); // 32
  task::sleep(500);

  chassis.drive_max_voltage = 4;
  chassis.drive_timeout = 750;
  chassis.turn_to_angle(-70);
  chassis.drive_timeout = 1000;
  // chassis.drive_distance(20);
  chassis.drive_max_voltage = 4;
  convDir = FORWARD;
  doAntiJam = false;
  chassis.drive_side_distance(20, 8, 1.5, 0, 20, 0, 1.5, 0, 20, 0);

  chassis.drive_timeout = 2000;
  chassis.drive_max_voltage = 4;
  chassis.drive_distance(-14);
  task::sleep(250);
  chassis.drive_distance(12);

  chassis.drive_max_voltage = 6;
  chassis.drive_distance(-36);  
  armToScore = true;
  armToStartPos = false;
  chassis.turn_to_angle(110);
  chassis.drive_distance(24);
}

void awp_goal_r() {

}

void awp_ring_r() {
  wallL.setPosition(0, deg);
  wallL.setVelocity(100, pct);
  chassis.drive_distance(1.2, chassis.get_absolute_heading(), 6, 0, .05, 200, 500);
  // wallL.spinTo(-100, deg, false); // lbLoad
  // hIntake.spin(fwd, 12, volt);
  // chassis.drive_distance(0.5, chassis.get_absolute_heading(), 6, 0, .05, 200, 5000);
  // intake.stop();
  // intake.spin(fwd, 12, volt);
  // task::sleep(50);
  // intake.stop();

  // wallL.spinFor(directionType::rev, 420, deg, true);
  //task::sleep(15000);

  wallL.spinTo(-240, deg, false);
  chassis.drive_distance(-5.2, chassis.get_absolute_heading(), 6, 0, 0.5, 200, 2000);
  Clamp.set(1);
  //task::sleep(250);

  //chassis.set_turn_exit_conditions(0.5, 300, 3000);
  chassis.turn_to_angle(-200, 10, 2, 300, 1000, 0.35, 0.03, 3.4, 15);
  // spin intake
  //thread intake1(intakecontrol);
  chassis.drive_distance(1.2, chassis.get_absolute_heading(), 6, 0, .05, 200, 2000, 10, 0, 5, 0, 0, 0, 0, 0); // 1st stack
  task::sleep(100);
  chassis.drive_distance(-1.9, chassis.get_absolute_heading(), 6, 0, .5, 200, 2000);
  chassis.turn_to_angle(-245);
  chassis.drive_distance(2.2, chassis.get_absolute_heading(), 6, 0, .05, 200, 5000); // second stack
  task::sleep(350);
  chassis.turn_to_angle(-160);
  chassis.drive_distance(1.2, chassis.get_absolute_heading(), 6, 0, .05, 200, 5000);
  task::sleep(250);
  chassis.drive_distance(-2.3, chassis.get_absolute_heading(), 6, 0, .05, 200, 5000);
  chassis.turn_to_angle(90);
  chassis.drive_distance(-5);
  intake.stop();
  //intake1.interrupt();
  // go to ladder?
}

void awp_ring_b() {
  wallL.setPosition(0, deg);
  wallL.setVelocity(100, pct);
  chassis.drive_distance(1.2, chassis.get_absolute_heading(), 6, 0, .05, 200, 500);
  // wallL.spinTo(-100, deg, false); // lbLoad
  // hIntake.spin(fwd, 12, volt);
  // chassis.drive_distance(0.5, chassis.get_absolute_heading(), 6, 0, .05, 200, 5000);
  // intake.stop();
  // intake.spin(fwd, 12, volt);
  // task::sleep(50);
  // intake.stop();

  // wallL.spinFor(directionType::rev, 420, deg, true);
  //task::sleep(15000);

  wallL.spinTo(-240, deg, false);
  chassis.drive_distance(-4.7, chassis.get_absolute_heading(), 6, 0, 0.5, 200, 2000);
  Clamp.set(1);
  //task::sleep(250);

  //chassis.set_turn_exit_conditions(0.5, 300, 3000);
  chassis.turn_to_angle(200, 10, 2, 300, 1000, 0.35, 0.03, 3.4, 15);
  // spin intake
  //thread intake1(intakecontrol);
  chassis.drive_distance(1.2, chassis.get_absolute_heading(), 6, 0, .05, 200, 5000, 10, 0, 5, 0, 0, 0, 0, 0); // 1st stack
  task::sleep(100);
  chassis.drive_distance(-1.4, chassis.get_absolute_heading(), 6, 0, .5, 200, 5000);
  chassis.turn_to_angle(245);
  chassis.drive_distance(2.5, chassis.get_absolute_heading(), 6, 0, .05, 200, 5000); // second stack
  task::sleep(350);
  chassis.turn_to_angle(160);
  chassis.drive_distance(1, chassis.get_absolute_heading(), 6, 0, .05, 200, 5000);
  task::sleep(250);
  chassis.drive_distance(-1.5, chassis.get_absolute_heading(), 6, 0, .05, 200, 5000);
  chassis.turn_to_angle(265);
  chassis.drive_distance(-6, chassis.get_absolute_heading(), 6, 0, .5, 200, 5000);
  intake.stop();
  //intake1.interrupt();
  // go to ladder?
}

void drive_test(){
  chassis.drive_distance(24, 90);
  task::sleep(1000);
  chassis.drive_distance(-24, 90);
  // chassis.drive_distance(8.4);
  // chassis.drive_distance(-4.2);
  // chassis.drive_distance(-8.4);
}

/*
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
  Doink.set(1);

  fIntake.spin(fwd, 12, volt);
  hIntake.spin(fwd, 6, volt);
  chassis.drive_distance(4.05, chassis.get_absolute_heading(), 12, 12, 1.5, 200, 1200, 4, 0, 50, 0, 0, 0, 0, 0);
  task::sleep(50);
  hIntake.stop();
  Doink.set(0); // grab mogo 
  chassis.drive_distance(-3.8, chassis.get_absolute_heading(), 12, 12, 1.5, 200, 5000, 4, 0, 50, 0, 0, 0, 0, 0);
  fIntake.stop();
  chassis.set_drive_constants(10, 10, 0, 40, 0); // first val can be 10 or 12
  Doink.set(1);
  task::sleep(30);
  chassis.drive_distance(1.5);
  chassis.drive_distance(-1.5, chassis.get_absolute_heading(), 6, 6, 1.5, 200, 1000);
  Doink.set(0);
  task::sleep(100);
  chassis.turn_to_angle(195);
  chassis.set_drive_constants(4, 10, 0, 40, 0); // first val can be 10 or 12
  chassis.drive_distance(-3.4, chassis.get_absolute_heading(), 6, 0);
  chassis.set_drive_constants(8, 10, 0, 40, 0); // first val can be 10 or 12
  Clamp.set(1);
  task::sleep(200);
  chassis.turn_to_angle(220);
  task::sleep(100);
  thread intake1(intakecontrol);
  //hIntake.spin(fwd, 12, volt);
  task::sleep(500);
  intake1.interrupt();
  intake.stop();
  //hIntake.stop();
  chassis.drive_distance(4.6);
  chassis.turn_to_angle(-230);
  Doink.set(1);
  task::sleep(10);
  chassis.drive_distance(3.7);
  chassis.turn_to_angle(-320);
  Doink.set(0);
  chassis.turn_to_angle(0);
  chassis.drive_distance(2);
  Clamp.set(0);
  task::sleep(100);
  chassis.turn_to_angle(20);
  chassis.drive_distance(1.2, chassis.get_absolute_heading(), 8, 0, 0.05, 200, 750);
  chassis.turn_to_angle(110, 6);
  chassis.set_drive_constants(8, 10, 0, 40, 0); // first val can be 10 or 12
  chassis.drive_distance(-2);
  chassis.set_drive_constants(12, 10, 0, 40, 0); // first val can be 10 or 12
  Clamp.set(1);
  thread intake2(intakecontrol);
  // fIntake.spin(fwd, 12, volt);
  // hIntake.spin(fwd, 12, volt);
  chassis.drive_distance(2.5);
  intake2.interrupt();
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
  chassis.drive_distance(4.05, chassis.get_absolute_heading(), 12, 12, 1.5, 200, 5000, 4, 0, 50, 0, 0, 0, 0, 0);
  task::sleep(50);
  hIntake.stop();
  Doink.set(0); // grab mogo 
  chassis.drive_distance(-3, chassis.get_absolute_heading(), 12, 12, 1.5, 200, 5000, 4, 0, 50, 0, 0, 0, 0, 0);
  fIntake.stop();
  Doink.set(1);
  task::sleep(30);
  chassis.drive_distance(1.5);
  //chassis.set_drive_constants(10, 20, 0, 20, 0); // first val can be 10 or 12
  chassis.drive_distance(-1.5, chassis.get_absolute_heading(), 6, 6, 1.5, 200, 1000);
  chassis.set_drive_constants(8, 10, 0, 40, 0); // first val can be 10 or 12
  Doink.set(0);
  task::sleep(100);
  chassis.turn_to_angle(192);
  chassis.drive_distance(-4, chassis.get_absolute_heading(), 6, 0, 0.5, 200, 2000);
  Clamp.set(1);
  thread intake1(intakecontrol);
  //hIntake.spin(fwd, 12, volt);
  task::sleep(400);
  intake1.interrupt();
  intake.stop();
  chassis.turn_to_angle(-120);
  chassis.drive_distance(2.5);
  chassis.turn_to_angle(-155);
  Doink.set(1);
  task::sleep(10);
  chassis.drive_distance(1.9, chassis.get_absolute_heading(), 8, 0, 0.05, 200, 1000);
  chassis.turn_to_angle(-250, 10, 2.0, 300, 1000);
  //chassis.drive_distance(1);
  chassis.turn_to_angle(-350, 6);
  task::sleep(100);
  Doink.set(0);
  chassis.turn_to_angle(45);
  chassis.drive_distance(1.5, chassis.get_absolute_heading(), 8, 0, 0.5, 200, 2000);
  Clamp.set(0);
  chassis.drive_distance(1.2, chassis.get_absolute_heading(), 8, 0, 0.5, 200, 2000);
  chassis.turn_to_angle(-60);
  chassis.drive_distance(-3, chassis.get_absolute_heading(), 8, 0, 0.5, 200, 2000);
  Clamp.set(1);
  task::sleep(250);
  intake.spin(fwd, 12, volt);
  chassis.drive_distance(3);
  
  // chassis.turn_to_angle(-120, 6);
  // chassis.set_drive_constants(5, 10, 0, 40, 0); // first val can be 10 or 12
  // chassis.drive_distance(-2);
  // chassis.turn_to_angle(60, 6);
  // Clamp.set(0);
  // chassis.turn_to_angle(-120, 6);
  // chassis.drive_distance(-3);
  // Clamp.set(1);
  // chassis.turn_to_angle(-90, 6);
  // fIntake.spin(fwd, 12, volt);
  // hIntake.spin(fwd, 12, volt);
  // chassis.drive_distance(3);
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
*/

/**
 * The expected behavior is to return to the start angle, after making a complete turn.
 */

void turn_test(){
  // // chassis.turn_to_angle(0);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(180);
  chassis.turn_to_angle(270);
  chassis.turn_to_angle(0);
}

/**
 * Should swing in a fun S shape.
 */

void swing_test(){
  chassis.right_swing_to_angle(-90);
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