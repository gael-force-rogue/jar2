#pragma once

#include "vex.h"

using namespace vex;

/**
 * @brief Publicly extends vex::pneumatics to add toggle functionality.
 * @param port Pneumatic port. (e.g. Brain.ThreeWirePort.A)
 */
class Pneumatic {
   private:
    vex::pneumatics pneumatic;

    bool isDeployed = false;

   public:
    Pneumatic(vex::triport::port port, bool startingMode) : pneumatic(port), isDeployed(startingMode) {};

    inline void open() {
        this->pneumatic.open();
    }

    inline void close() {
        this->pneumatic.close();
    }

    inline void toggle() {
        isDeployed = !isDeployed;
        if (isDeployed) {
            pneumatic.close();
        } else {
            pneumatic.open();
        };
    };
};

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
    vex::motor motor;
    vex::optical optical;
    float targetVelocity = 0;
    int allianceColor;

    bool shouldStopForNextRing = false;

   public:
    bool antiJamEnabled = true;
    bool colorSortEnabled = true;

    Intake(int port, bool reversed, int opticalPort)
        : motor(port, reversed), optical(opticalPort) {};

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

    /**
     * @brief Starts a loop for anti-jam and color sort. Both can be disabled.
     */
    inline void startBackgroundTaskLoop() {
        while (true) {
            if (antiJamEnabled && motor.velocity(vex::rpm) < 1 && targetVelocity != 0) {
                motor.spin(vex::fwd, -100, vex::pct);
                delay(100);
                motor.spin(vex::fwd, 100, vex::pct);
                delay(100);
                motor.spin(vex::fwd, targetVelocity, vex::pct);
            };

            if (colorSortEnabled) {
                double hue = optical.hue();
                bool isRed = hue < 15;
                bool isBlue = hue > 200;

                if (allianceColor == RED) {
                    if (isRed && shouldStopForNextRing) {
                        motor.stop();
                    } else if (isBlue) {
                        // EJECT
                    };
                } else if (allianceColor == BLUE) {
                    if (isBlue && shouldStopForNextRing) {
                        motor.stop();
                    } else if (isRed) {
                        // EJECT
                    };
                };
            };
        };
    };
};

enum LiftState {
    STANDBY = -30,
    LOAD = 0
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

    float position();
    void spin(float velocity);
    void startMaintainingPosition(float kP, float kD, float maxSpeed);

    inline void spinTo(float newTarget) {
        this->driverInterrupt = false;
        this->target = newTarget;
    };
};