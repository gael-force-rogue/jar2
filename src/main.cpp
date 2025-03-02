#include "config.h"
#include "devices.h"
#include "vex.h"

using namespace vex;
competition Competition;

controller Controller;

Drive chassis(
    // drive_setup enum
    TANK_TWO_ROTATION,

    // Left Motors:
    motor_group(left1, left2, left3),

    // Right Motors:
    motor_group(right1, right2, right3),

    // Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
    PORT3,

    // Input your wheel diameter. (4" omnis are actually closer to 4.125"):
    3.25,

    // External ratio, must be in decimal, in the format of input teeth/output teeth.
    // If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
    // If the motor drives the wheel directly, this value is 1:
    1,

    // Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
    // For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
    360,

    /*---------------------------------------------------------------------------*/
    /*                                  PAUSE!                                   */
    /*                                                                           */
    /*  The rest of the drive constructor is for robots using POSITION TRACKING. */
    /*  If you are not using position tracking, leave the rest of the values as  */
    /*  they are.                                                                */
    /*---------------------------------------------------------------------------*/

    // If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

    // FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
    // LF:      //RF:
    PORT1, -PORT2,

    // LB:      //RB:
    PORT3, -PORT4,

    // If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
    // If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
    // If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
    PORT11,

    // Input the Forward Tracker diameter (reverse it to make the direction switch):
    2,

    // Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
    // For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
    // This distance is in inches:
    -2,

    // Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
    PORT21,

    // Sideways tracker diameter (reverse to make the direction switch):
    2.75,

    // Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
    -1.25);

bool auto_started = false;
void pre_auton() {
    default_constants();
    lift.calibrate();

    while (!auto_started) {
        Brain.Screen.clearScreen();
        Brain.Screen.printAt(5, 20, "JAR Template v1.2.0");
        Brain.Screen.printAt(5, 40, "Battery Percentage: %f", Brain.Battery.capacity());
        Brain.Screen.printAt(5, 60, "Chassis Heading Reading: %f", chassis.get_absolute_heading());
        Brain.Screen.printAt(5, 80, "Lift: %f", lift.position());

        delay(20);
    };
};

void autonomous(void) {
    auto_started = true;
    float start = vex::timer::system();

    skills();

    float end = vex::timer::system();
    printf("Auton took: %f ms\n", end - start);

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

void usercontrol(void) {
    digital_out Clamp = digital_out(Brain.ThreeWirePort.B);

    while (1) {
        chassis.control_arcade();

        // Intake
        if (Controller.ButtonR2.pressing()) {
            intake.spin(100);
        } else if (Controller.ButtonR1.pressing()) {
            intake.spin(-100);
        } else {
            intake.stop(coast);
            if (Controller.ButtonLeft.pressing()) {
                frontstageMotor.spin(fwd, 100, pct);
            }
        };

        // Lift
        if (Controller.ButtonL1.pressing()) {
            lift.spin(100);
        } else if (Controller.ButtonL2.pressing()) {
            lift.spin(-100);
        } else if (lift.driverInterrupt) {
            lift.spin(0);
        };

        // Clamp
        if (Controller.ButtonA.pressing()) {
            Clamp.set(true);
        } else if (Controller.ButtonB.pressing()) {
            Clamp.set(false);
        };

        // Knocker
        // if (knockerYButton.isNewPress()) {
        //     if (Knocker.value() == 0) {
        //         Knocker.set(true);
        //     } else {
        //         Knocker.set(false);
        //     };
        // };

        // Lift Up
        if (Controller.ButtonUp.pressing()) {
            lift.spinTo(20);
            lift.driverInterrupt = false;
        };

        delay(20);
    };
};

void liftThreadF() {
    lift.startBackgroundTaskLoop(1, 5.6, 100);
};

void intakeThreadF() {
    intake.startBackgroundTaskLoop();
};

int main() {
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    vex::thread liftThread(liftThreadF);
    vex::thread intakeThread(intakeThreadF);

    pre_auton();

    // bool success = Brain.Screen.drawImageFromFile("logocroppednoborder-i2.png", 120, 0);
    // printf("Success: %d\n", success);

    while (true) {
        delay(100);
    }
};
