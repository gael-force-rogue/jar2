#include "devices.h"

void Intake::startBackgroundTaskLoop() {
    while (true) {
        if (antiJamEnabled && motor.velocity(vex::rpm) < 1 && targetVelocity != 0) {
            printf("Velocity: %f\n", motor.velocity(vex::rpm));
            motor.spin(vex::fwd, -100, vex::pct);
            delay(400);
            motor.spin(vex::fwd, 100, vex::pct);
            delay(200);
            motor.spin(vex::fwd, targetVelocity, vex::pct);
            delay(200);
        };

        if (colorSortEnabled) {
            double hue = optical.hue();
            bool isRed = optical.color() == vex::color::red;
            bool isBlue = hue >= 110 && hue <= 250;

            if (this->allianceColor == RED) {
                if (isRed && shouldStopForNextRing) {
                    motor.stop();
                } else if (isBlue) {
                    this->ejectRing();
                };
            } else if (this->allianceColor == BLUE) {
                if (isBlue && shouldStopForNextRing) {
                    motor.stop();
                } else if (isRed) {
                    this->ejectRing();
                };
            };
        };
    };
};

float Lift::position() {
    float angle = (float)rotation.angle(rotationUnits::deg);
    if (angle > 300) return angle - 180;
    return angle;
};

void Lift::spin(float velocity) {
    this->driverInterrupt = true;
    this->motor.spin(vex::fwd, velocity, vex::pct);
};

void Lift::startBackgroundTaskLoop(float kP, float kD, float maxSpeed) {
    float previousError = 0;
    this->motor.setBrake(hold);
    while (true) {
        if (!this->driverInterrupt) {
            float error = this->target - this->position();
            float derivative = error - previousError;

            float power = (kP * error) + (kD * derivative);
            power = clamp(power, -maxSpeed, maxSpeed);

            if (previousError > 0 && error < 0) {
                derivative = 0;
            };

            // DO NOT USE HELPER SPIN FUNCTION
            if (fabs(error) > 3) {
                this->motor.spin(fwd, power, pct);
            } else {
                this->motor.spin(fwd, 0, pct);
                this->motor.stop(hold);
            };
            previousError = error;
        };

        delay(20);
    };
};

void Lift::spinTo(float newTarget) {
    this->driverInterrupt = false;
    this->target = newTarget;
};