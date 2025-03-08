#include "config.h"

void blue_solo_awp(bool half_only, bool elims) {
    digital_out Clamp = digital_out(Brain.ThreeWirePort.B);
    Clamp.set(false);
    chassis.set_coordinates(0, 0, 0);
    odom_constants();
    intake.setAllianceColor(BLUE);
    intake.colorSortEnabled = true;

    // Alliance
    lift.spin(100);
    delay(700);
    lift.spinTo(-5);

    chassis.set_drive_exit_conditions(0.5, 300, 1200);
    // chassis.drive_to_pose(-16.7, -19.8, 23.3, 0.1, 0, 0, 8, 4);
    chassis.drive_to_point(18, -17, 0, 8, 4, 1, 100, 2700);
    chassis.drive_max_voltage = 4;
    chassis.drive_settle_error = 0.5;
    chassis.drive_distance(-17, -24.6);
    Clamp.set(true);
    delay(200);

    // 24.6 -41.7 168
    chassis.turn_to_angle(-191);
    intake.spin();
    chassis.drive_to_pose(24.6, -41.7, 168, 0.1, 0, 0, 10, 6);
    chassis.swing_max_voltage = 6;
    chassis.swing_timeout = 1500;
    chassis.left_swing_to_angle(-145);
    chassis.drive_timeout = 700;
    chassis.drive_max_voltage = 9;
    chassis.drive_distance(25, -145);
    chassis.drive_distance(10, -145);

    // Standalones
    chassis.drive_timeout = 700;
    chassis.swing_max_voltage = 10;
    chassis.drive_distance(-20, 145);
    chassis.left_swing_to_angle(-15);
    chassis.drive_distance(20, 0);
};