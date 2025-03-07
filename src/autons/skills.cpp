#include <string>

#include "config.h"

void printpoint(std::string name) {
    printf("%s: %f, %f %f\n", name.c_str(), chassis.get_X_position(), chassis.get_Y_position(), chassis.get_absolute_heading());
};

void skills() {
    odom_constants();
    digital_out Clamp = digital_out(Brain.ThreeWirePort.B);
    intake.setAllianceColor(RED);

    chassis.set_coordinates(0, 0, 48);

    // Alliance
    lift.driverInterrupt = false;
    lift.spinTo(220);
    delay(1000);
    lift.coast();

    // Clamp
    // float X_position, float Y_position, float drive_min_voltage, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout
    // chassis.drive_to_point(-4.5, -5, 0, 10, 8, 1, 50, 2000);
    // chassis.drive_distance(-12, 34);
    chassis.drive_settle_error = 2;
    chassis.drive_timeout = 700;
    chassis.swing_timeout = 350;
    chassis.drive_min_voltage = 5;
    chassis.drive_distance(-11);
    chassis.left_swing_to_angle(26);
    chassis.drive_distance(-7);
    Clamp.set(true);
    lift.spinTo(50);
    delay(300);
    odom_constants();

    // Ring 1
    chassis.turn_to_point(-33, -8);
    lift.spinTo(-2);
    intake.spin(100);
    chassis.drive_to_point(-33, -8, 0, 10, 4, 7, 50, 2000);

    // Ring 2 waypoint
    chassis.left_swing_to_angle(-135);
    chassis.drive_to_point(-53, -28, 4, 12, 8, 8, 50, 4000);

    lift.spinTo(22);

    // Ring 2
    intake.antiJamEnabled = false;
    chassis.drive_settle_error = 2;
    chassis.drive_to_point(-80, -36);
    delay(500);

    // Ring 3 & Neutral
    chassis.turn_settle_error = 1;
    chassis.turn_timeout = 1500;
    chassis.drive_to_point(-53, -29, 0, 5, 8, 0.5, 400, 3000);
    chassis.turn_to_angle(-180);

    printpoint("Neutral Alignment");

    chassis.drive_max_voltage = 7;

    intake.stop(hold);
    frontstageMotor.spin(fwd, 100, pct);
    chassis.drive_settle_error = 1;
    chassis.drive_to_pose(-56, -46, 180, 0.3, 0, 0, 5, 8);
    chassis.drive_distance(4);
    conveyerMotor.spin(fwd, -50, pct);
    // conveyerMotor.stop(coast);
    lift.spin(100);
    delay(1100);
    frontstageMotor.stop();
    intake.spin();
    intake.antiJamEnabled = true;
    lift.spinTo(-5);
    delay(1000);

    chassis.turn_timeout = 1200;
    chassis.drive_distance(-20);
    delay(700);
    chassis.drive_distance(15, -180);
    delay(500);
    chassis.drive_to_point(-53, -32, 0, 7, 8, 1, 400, 3000);

    // Ring 4, 5, 6
    chassis.turn_to_angle(88);
    lift.spinTo(-5);

    chassis.drive_to_point(-16, -35, 0, 10, 8, 4, 200, 2000);
    delay(300);
    chassis.drive_max_voltage = 5;
    // chassis.drive_to_point(-14, -35, 0, 7, 8, 3, 200, 1000);
    chassis.drive_to_point(2, -35, 0, 4, 8, 3, 200, 1500);

    // Ring 6 & Deposit
    odom_constants();
    chassis.drive_settle_error = 3;
    chassis.drive_max_voltage = 7;
    chassis.drive_distance(-29);
    chassis.drive_max_voltage = 10;
    chassis.turn_to_angle(145);
    chassis.drive_distance(23);
    chassis.swing_timeout = 1500;
    chassis.turn_to_angle(180);
    chassis.turn_to_angle(-75);
    Clamp.set(false);
    chassis.drive_distance(-23);

    //
    lift.spinTo(22);
    chassis.drive_to_point(-53, -30, 8, 12, 8, 20, 50, 4000);
    chassis.drive_to_point(-100, -33, 0, 10, 8, 1, 200, 6000);
    intake.antiJamEnabled = false;
    chassis.turn_to_angle(165);
    intake.stop(coast);
    chassis.drive_max_voltage = 5;
    chassis.drive_timeout = 5000;
    chassis.drive_distance(-31);
    delay(100);
    Clamp.set(true);

    chassis.drive_max_voltage = 11;

    chassis.turn_timeout = 1200;
    chassis.turn_to_angle(145);
    chassis.drive_distance(25);
    chassis.turn_to_angle(37.5);
    Clamp.set(false);
    delay(500);
    chassis.drive_distance(-29);
    intake.stop();

    chassis.turn_timeout = 1500;
    chassis.drive_settle_error = 1;
    chassis.drive_to_pose(-104, -15, 0, 0.3, 0, 0, 10, 3000);
    chassis.turn_to_angle(180);
    printpoint("2nd Empty Mogo");
    chassis.drive_max_voltage = 5.5;
    chassis.drive_to_point(-107, 14, 0, 6, 8, 1, 300, 5000);
    delay(300);
    Clamp.set(true);
    delay(200);

    chassis.turn_timeout = 2000;
    chassis.turn_settle_time = 400;
    chassis.turn_to_angle(-90);
    chassis.drive_to_pose(-110, 13, -90, 0.2, 0, 0, 6, 6);
    chassis.turn_to_angle(-90);

    intake.spin(-25);
    lift.spin(100);
    delay(1000);
    lift.spinTo(-5);

    chassis.drive_distance(-20);
};