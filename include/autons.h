#pragma once
#include "JAR-Template/drive.h"

class Drive;

extern Drive chassis;

void default_constants();

void ladyBrown(double targetDegrees);

void grush_r();
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
void awp_goal_r();
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