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
    lift.spinTo(250);
    delay(1300);

    // Clamp
    // float X_position, float Y_position, float drive_min_voltage, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout
    chassis.drive_to_point(-9, -13, 0, 10, 8, 2, 50, 2000);
    chassis.drive_stop(coast);
    delay(300);
    Clamp.set(true);
    lift.spinTo(-5);
    delay(300);

    // Ring 1
    chassis.turn_to_angle(-100);
    intake.spin(100);
    chassis.drive_to_point(-33, -8);

    // Ring 2
    chassis.left_swing_to_angle(-135);
    chassis.drive_to_point(-53, -26);

    // Ring 3
    lift.spinTo(20);
    chassis.drive_to_point(-73, -31);
    delay(500);

    // Ring 4 & Neutral
    chassis.drive_to_point(-53, -26);
    chassis.turn_to_angle(-180);
    intake.stop();
    frontstageMotor.spin(fwd, 100, pct);
    chassis.drive_to_point(-55, -45);
    chassis.turn_to_angle(-180);
    lift.spinTo(160);

    // frontstageMotor.stop();
    // intake.spin(100);
};