#pragma once
#include "JAR-Template/drive.h"

extern Drive chassis;

void default_constants();

/// TEST AUTONS
void drive_test();
void turn_test();
void swing_test();
void full_test();
void odom_test();
void tank_odom_test();
void holonomic_odom_test();

/// USER AUTONS
void red_solo_awp(bool half_only, bool elims);
void blue_solo_awp(bool half_only, bool elims);
void skills();