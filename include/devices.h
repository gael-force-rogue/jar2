#pragma once

#include "vex.h"

using namespace vex;

enum AllianceColor {
    RED,
    BLUE
};

/**
 * @brief Intake with anti-jam and color sort.
 * @param port Motor port.
 * @param reversed Whether the motor is reversed.
 * @param opticalPort Optical sensor port.
 */
class Intake {
   private:
    vex::motor_group motor;
    vex::optical optical;
    float targetVelocity = 0;
    int allianceColor;

    bool shouldStopForNextRing = false;

    /**
     * @brief Ejects a ring.
     */
    inline void ejectRing() {
        wait(15, msec);
        this->stop();
        wait(1000, msec);
        this->spin(100);
        wait(20, msec);
    };

   public:
    bool antiJamEnabled = true;
    bool colorSortEnabled = true;

    Intake(motor_group motorGroup, int opticalPort)
        : motor(motorGroup), optical(opticalPort) {};

    inline void setAllianceColor(int allianceColor) {
        this->allianceColor = allianceColor;
    };

    inline void stopForNextRing() {
        spin(100);
        this->shouldStopForNextRing = true;
    };

    /**
     * @brief Spins the intake at a specified velocity.
     */
    inline void spin(float velocity = 100) {
        targetVelocity = velocity;
        motor.spin(vex::fwd, velocity, vex::pct);
    };

    inline void stop(vex::brakeType type = vex::brakeType::hold) {
        this->motor.stop(type);
        this->spin(0);
    };

    /**
     * @brief Starts a loop for anti-jam and color sort. Both can be disabled.
     */
    void startBackgroundTaskLoop();
};

/**
 * Converts an angle to an equivalent one in the range [-360, 360].
 *
 * @param angle The angle to be reduced in degrees.
 * @return Reduced angle.
 */
inline float reduce_negative_360_to_360(float angle) {
    while (!(angle >= -360 && angle <= 360)) {
        if (angle < -360) {
            angle += 720;
        }
        if (angle > 360) {
            angle -= 720;
        }
    }
    return angle;
};

/**
 * @brief Lift with built-in PID and driver interrupt.
 * @param port Motor port.
 * @param reversed Whether the motor is reversed.
 * @param rotationPort Rotation sensor port.
 * @param rotationReversed Whether the rotation sensor is reversed.
 */
class Lift {
   private:
    vex::motor motor;
    vex::rotation rotation;
    float target = 0;

   public:
    bool driverInterrupt = true;

    Lift(int port, bool reversed, int rotationPort, bool rotationReversed)
        : motor(port, reversed), rotation(rotationPort, rotationReversed) {};

    inline void calibrate() {
        motor.setBrake(vex::brakeType::hold);
        rotation.resetPosition();
        rotation.setPosition(0, vex::rotationUnits::deg);
    };

    inline void coast() {
        this->driverInterrupt = true;
        this->motor.stop(vex::brakeType::coast);
    };

    float position();
    void spin(float velocity);
    void startBackgroundTaskLoop(float kP, float kD, float maxSpeed);

    void spinTo(float newTarget);
};