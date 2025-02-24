#include "config.h"

brain Brain;

motor left1 = motor(PORT20, ratio6_1, false);
motor left2 = motor(PORT16, ratio6_1, true);
motor left3 = motor(PORT7, ratio6_1, true);

motor right1 = motor(PORT9, ratio6_1, true);
motor right2 = motor(PORT8, ratio6_1, false);
motor right3 = motor(PORT10, ratio6_1, false);

motor conveyerMotor = motor(PORT12, ratio6_1, true);
motor frontstageMotor = motor(PORT4, ratio6_1, true);

Intake intake = Intake(motor_group(conveyerMotor, frontstageMotor), PORT5);
Lift lift = Lift(PORT18, true, PORT14, false);