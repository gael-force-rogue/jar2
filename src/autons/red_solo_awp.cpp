#include <string>

#include "config.h"

void red_solo_awp(bool half_only, bool elims) {
    digital_out Clamp = digital_out(Brain.ThreeWirePort.B);
    Clamp.set(false);
    chassis.set_coordinates(0, 0, 0);
    odom_constants();
    intake.setAllianceColor(RED);
    intake.colorSortEnabled = true;

    // Alliance
    lift.spin(100);
    delay(700);
    lift.spinTo(-5);

    // Clamp
    chassis.set_drive_exit_conditions(0.5, 300, 1200);
    // chassis.drive_to_pose(-16.7, -19.8, 23.3, 0.1, 0, 0, 8, 4);
    chassis.drive_to_point(-16.7, -19.8, 0, 8, 4, 1, 100, 2700);
    chassis.drive_max_voltage = 4;
    chassis.drive_settle_error = 0.5;
    chassis.drive_distance(-17, 24.6);
    Clamp.set(true);
    delay(200);

    // Stack
    chassis.turn_to_angle(191);
    intake.spin();
    chassis.drive_to_pose(-26, -46, 146, 0.1, 0, 0, 6, 5);
    chassis.swing_max_voltage = 6;
    chassis.swing_timeout = 1500;
    chassis.right_swing_to_angle(145);
    chassis.drive_timeout = 700;
    chassis.drive_max_voltage = 9;
    chassis.drive_distance(25, 145);
    chassis.drive_distance(10, 145);

    // Standalones
    chassis.drive_timeout = 700;
    chassis.swing_max_voltage = 10;
    chassis.drive_distance(-20, 145);
    chassis.right_swing_to_angle(-15);
    chassis.drive_distance(20, 0);

    // Pathway Ring
    intake.stopForNextRing();
    chassis.drive_settle_error = 15;
    chassis.drive_to_point(-6.1, -9.8, 0, 12, 8, 10, 50, 3000);
    Clamp.set(false);
    chassis.drive_settle_error = 1;
    chassis.drive_to_pose(-13.7, 0.3, 319, 0.2, 0, 0, 6, 6);

    // Travel to mogo
    chassis.drive_to_point(-32.1, 23.4, 0, 10, 8, 1, 200, 3000);
    chassis.turn_to_angle(45);
    chassis.drive_to_point(-51, 8.2, 0, 6, 8, 1, 200, 3000);
    Clamp.set(true);

    // Turn to touch
    chassis.drive_max_voltage = 12;
    chassis.swing_max_voltage = 12;

    lift.spinTo(160);
    chassis.left_swing_to_angle(180);
};

// void red_solo_awp(bool half_only, bool elims) {
//     digital_out Clamp = digital_out(Brain.ThreeWirePort.B);
//     chassis.set_coordinates(0, 0, 0);
//     odom_constants();
//     Clamp.set(false);
//     intake.setAllianceColor(RED);
//     intake.colorSortEnabled = true;

//     // Alliance
//     lift.spin(100);
//     delay(700);
//     lift.spinTo(-5);

//     // Clamp
//     chassis.swing_timeout = 600;
//     chassis.drive_settle_error = 1;
//     chassis.drive_timeout = 2000;
//     chassis.turn_timeout = 1000;
//     chassis.drive_to_point(-2, -21.5, 0, 12, 8, 1, 400, 5000);
//     chassis.right_swing_to_angle(85);
//     printpoint("Clamp");
//     chassis.drive_max_voltage = 4;
//     chassis.drive_distance(-23);
//     delay(200);
//     Clamp.set(true);
//     delay(200);

//     // Stack
//     chassis.drive_max_voltage = 12;
//     chassis.swing_timeout = 700;
//     chassis.turn_timeout = 1000;
//     chassis.turn_to_angle(180);
//     // -28, -46
//     intake.spin();
//     chassis.drive_settle_error = 1;
//     chassis.drive_timeout = 3000;
//     chassis.drive_to_pose(-26, -42, 145, 0.1, 0, 0, 10, 8);
//     // chassis.drive_distance(39);
//     chassis.swing_timeout = 700;
//     chassis.right_swing_to_angle(145);
//     chassis.drive_distance(20);
//     chassis.drive_distance(15, 150);
//     delay(500);

//     // Standalone
//     chassis.swing_timeout = 1000;
//     chassis.drive_distance(-25);
//     chassis.right_swing_to_angle(-30);
//     chassis.drive_distance(20);

//     // Corner
//     chassis.drive_max_voltage = 11;
//     chassis.drive_timeout = 3000;
//     chassis.swing_timeout = 700;
//     // chassis.left_swing_to_angle(90);

//     chassis.drive_settle_error = 4;
//     chassis.drive_to_point(13.5, -33, 0, 12, 8, 3, 200, 3000);
//     chassis.turn_to_angle(100);
//     // 1
//     chassis.drive_settle_error = 2;
//     chassis.drive_timeout = 570;
//     chassis.drive_max_voltage = 12;
//     chassis.drive_distance(30);
//     chassis.drive_distance(-20, 100);
//     // 2
//     chassis.drive_distance(30, 100);
//     chassis.drive_distance(-20, 100);
//     // 3
//     // chassis.drive_distance(30, 100);
//     // chassis.drive_distance(-20, 100);
//     // 4
//     // chassis.drive_distance(30, 80);
//     // chassis.drive_stop(coast);
//     lift.spinTo(40);
//     chassis.drive_to_point(-45, -21, 6, 12, 8, 1, 200, 5000);
// };
