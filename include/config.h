#pragma once

#include "devices.h"

using namespace vex;

extern brain Brain;

extern motor left1;
extern motor left2;
extern motor left3;
extern motor right1;
extern motor right2;
extern motor right3;

extern motor conveyerMotor;
extern motor frontstageMotor;

extern Intake intake;
extern Lift lift;

void vexcodeInit(void);

inline void printpoint(std::string name) {
    printf("%s: %f, %f %f\n", name.c_str(), chassis.get_X_position(), chassis.get_Y_position(), chassis.get_absolute_heading());
};