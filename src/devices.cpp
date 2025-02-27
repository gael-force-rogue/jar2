#include "devices.h"

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

            printf("Lift: %f, %f\n", derivative, power);

            // DO NOT USE HELPER SPIN FUNCTION
            if (fabs(error) > 5) {
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