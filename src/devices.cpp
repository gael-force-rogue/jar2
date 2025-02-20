#include "devices.h"

float Lift::position() {
    float angle = (float)rotation.angle(rotationUnits::deg);
    if (angle > 220) return angle - 180;
    return angle;
};

void Lift::spin(float velocity) {
    this->driverInterrupt = true;
    this->motor.spin(vex::fwd, velocity, vex::pct);
};

void Lift::startMaintainingPosition(float kP, float kD, float maxSpeed) {
    float previousError = 0;
    this->motor.setBrake(hold);
    while (true) {
        if (!this->driverInterrupt) {
            float error = this->target - this->position();
            float derivative = error - previousError;
            previousError = error;

            float power = (kP * error) + (kD * derivative);
            power = clamp(power, -maxSpeed, maxSpeed);

            if (previousError > 0 && error < 0) {
                derivative = 0;
            };

            // DO NOT USE HELPER SPIN FUNCTION
            if (fabs(error) > 2) {
                this->motor.spin(fwd, power, pct);
            } else {
                this->motor.spin(fwd, 0, pct);
                this->motor.stop(hold);
            };
        };

        delay(20);
    };
};