#include "config.h"

void red_solo_awp(bool half_only, bool elims) {
    digital_out Clamp = digital_out(Brain.ThreeWirePort.B);
    chassis.set_coordinates(0, 0, 0);
    odom_constants();
    Clamp.set(false);
    intake.setAllianceColor(RED);
    intake.colorSortEnabled = true;

    // Alliance
    lift.spin(100);
    delay(700);
    lift.coast();

    // Clamp
    chassis.swing_timeout = 600;
    chassis.drive_distance(-35);
    chassis.right_swing_to_angle(85);
    lift.spinTo(-3);

    chassis.drive_max_voltage = 6;
    chassis.drive_distance(-20);
    delay(200);
    Clamp.set(true);

    // Stack
    chassis.swing_timeout = 700;
    chassis.right_swing_to_angle(177);
    // -28, -46
    intake.spin();
    chassis.drive_settle_error = 1;
    chassis.drive_timeout = 2000;
    chassis.drive_distance(35);
    chassis.swing_timeout = 700;
    chassis.right_swing_to_angle(145);

    chassis.drive_distance(20);
    chassis.drive_distance(15);

    // Standalone
    chassis.swing_timeout = 1000;
    chassis.drive_distance(-25);
    chassis.right_swing_to_angle(0);
    chassis.drive_distance(20);

    // Corner
    chassis.drive_max_voltage = 12;
    chassis.drive_timeout = 3000;
    chassis.swing_timeout = 700;
    chassis.left_swing_to_angle(90);
    // 1
    chassis.drive_settle_error = 8;
    chassis.drive_to_pose(16, -33, 100, 0.1, 0, 0, 12, 8);
    chassis.drive_settle_error = 2;
    chassis.drive_timeout = 700;
    chassis.drive_distance(20);
    chassis.drive_distance(-20, 100);
    // 2
    chassis.drive_distance(20, 100);
    chassis.drive_distance(-20, 100);
    // 3
    chassis.drive_distance(20, 100);
    chassis.drive_distance(-20, 100);
    // 4
    chassis.drive_distance(20, 100);
    chassis.drive_stop(coast);
    chassis.drive_to_point(-43, -21, 6, 12, 8, 1, 200, 5000);
};
