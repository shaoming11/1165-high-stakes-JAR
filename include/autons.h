#pragma once
#include "JAR-Template/drive.h"

class Drive;

extern Drive chassis;

void default_constants();

void ladyBrown(double targetDegrees);

void eight_r(); // 8 ring red
void gr_five(); // goal side, red, 5 ring + alliance, elims
void grq_four(); // goal, red, qual, 4 ring + alliance
void grush_r2();
void grush_b();
void gdisrupt_r();
void gdisrupt_b();
void five_r();
void five_b();
void five_r_wall();
void five_b_wall();
void awp_solo_r();
void awp_solo_b();
void awp_goal_r(); // goal side, red, 3 ring corner
void awp_goal_b();
void awp_ring_r();
void awp_ring_b();
void drive_test();
void turn_test();
void swing_test();
void full_test();
void odom_test();
void tank_odom_test();
void holonomic_odom_test();