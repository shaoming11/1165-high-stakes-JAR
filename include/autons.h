#pragma once
#include "JAR-Template/drive.h"

class Drive;

extern Drive chassis;

void default_constants();

void ladyBrown(double targetDegrees);

void eight_r(); // 8 ring red
void eight_b();
void five_r(); // 1 + 4 ring 
void five_b();
void gre_four(); //
void gre_five(); // 1 4
void gre_six(); // 1 5, goal side red 6 rng lliance elims
void gbe_five();
void grq_four(); // goal, red, qual, 4 ring + alliance
void gbq_four();
void awp_solo_r();
void awp_solo_b();

void drive_test();
void turn_test();
void swing_test();
void full_test();
void odom_test();
void tank_odom_test();
void holonomic_odom_test();