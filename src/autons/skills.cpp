#include <string>

#include "config.h"

void printpoint(std::string name) {
    printf("%s: %f, %f\n", name.c_str(), chassis.get_X_position(), chassis.get_Y_position());
};

void skills() {
    odom_constants();
    digital_out Clamp = digital_out(Brain.ThreeWirePort.B);
    intake.setAllianceColor(RED);
    intake.antiJamEnabled = false;

    chassis.set_coordinates(0, 0, 48);

    // Alliance
    lift.driverInterrupt = false;
    lift.spinTo(220);
    delay(1300);
    lift.coast();

    // Clamp
    // float X_position, float Y_position, float drive_min_voltage, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout
    // chassis.drive_to_point(-4.5, -5, 0, 10, 8, 1, 50, 2000);
    // chassis.drive_distance(-12, 34);
    chassis.drive_settle_error = 2;
    chassis.drive_timeout = 1000;
    chassis.swing_timeout = 350;
    chassis.drive_distance(-11);
    chassis.left_swing_to_angle(26);
    chassis.drive_distance(-3);
    delay(300);
    Clamp.set(true);
    lift.spinTo(50);
    delay(300);
    odom_constants();

    // Ring 1
    chassis.turn_to_point(-33, -8);
    lift.spinTo(-2);
    intake.spin(100);
    chassis.drive_to_point(-33, -8, 0, 10, 8, 7, 50, 2000);

    // Ring 2 waypoint
    chassis.left_swing_to_angle(-135);
    chassis.drive_to_point(-53, -24, 4, 12, 8, 2, 50, 4000);

    lift.spinTo(22);

    // Ring 2
    chassis.drive_settle_error = 5;
    chassis.drive_to_point(-75, -30);
    delay(500);

    // Ring 3 & Neutral
    chassis.turn_settle_error = 0.1;
    chassis.drive_to_point(-49, -24, 0, 7, 8, 0.25, 400, 3000);
    chassis.turn_to_angle(-180);

    chassis.drive_max_voltage = 7;

    intake.stop(coast);
    frontstageMotor.spin(fwd, 100, pct);
    chassis.drive_distance(28);
    intake.spin(-30);
    lift.spinTo(170);
    delay(1000);

    chassis.drive_to_point(-49, -26, 0, 7, 8, 1, 400, 3000);
    intake.spin();

    chassis.turn_to_angle(90);
    lift.spinTo(0);

    chassis.drive_to_point(-13, -29.5, 0, 9, 8, 1, 200, 3000);
    chassis.drive_to_point(-2, -29.5, 0, 9, 8, 1, 200, 3000);
    chassis.drive_to_point(-13, -29.5, 0, 9, 8, 1, 200, 3000);
};