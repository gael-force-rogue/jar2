#include <string>

#include "config.h"

void printpoint(std::string name) {
    printf("%s: %f, %f\n", name.c_str(), chassis.get_X_position(), chassis.get_Y_position());
};

void skills() {
    intake.setAllianceColor(RED);

    pneumatics Clamp = pneumatics(Brain.ThreeWirePort.B);

    chassis.set_coordinates(0, 0, 48);

    // Alliance
    lift.driverInterrupt = false;
    lift.spinTo(200);
    delay(800);

    // Clamp
    chassis.drive_settle_error = 3;
    chassis.drive_distance(-12);
    lift.spinTo(5);
    chassis.swing_timeout = 400;
    chassis.left_swing_to_angle(33);
    chassis.drive_distance(-4);
    Clamp.set(true);
    delay(1000);

    // Ring 1
    chassis.turn_timeout = 700;
    chassis.turn_to_angle(-100);
    intake.spin(100);
    chassis.drive_to_pose(-25, -5, -110);
    printpoint("Ring 1");

    // Ring 2
    chassis.turn_timeout = 500;
    chassis.turn_to_point(-49, -25);
    chassis.drive_settle_error = 9;
    chassis.drive_to_point(-49, -25);
    lift.spinTo(20);
    chassis.drive_settle_error = 3;
    chassis.drive_to_point(-75, -33);

    // Neutral
    chassis.drive_to_point(-61, -40);
    chassis.right_swing_to_angle(-180);

    // DO NOT EDIT

    chassis.drive_stop(hold);
    wait(1000, msec);
    chassis.drive_stop(coast);

    while (1) {
        Brain.Screen.clearScreen();
        Brain.Screen.printAt(5, 20, "X: %f", chassis.get_X_position());
        Brain.Screen.printAt(5, 40, "Y: %f", chassis.get_Y_position());
        Brain.Screen.printAt(5, 60, "Heading: %f", chassis.get_absolute_heading());
        Brain.Screen.printAt(5, 80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
        Brain.Screen.printAt(5, 100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
        delay(20);
    };
};