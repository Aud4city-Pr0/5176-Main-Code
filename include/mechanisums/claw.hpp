#pragma once
//-----------------------------------------
// File name: claw.hpp
// Creation date: 7/28/26
// Created By: Zach D
// Description: The claw mechanism class, contains methods for controling the claw
//-----------------------------------------

// File includes
//--------------
#include "pros/motors.hpp"
#include "pros/rotation.h"
#include "EZ-Template/piston.hpp"
#include "EZ-Template/PID.hpp"
#include "pros/rotation.hpp"

// the claw class
namespace ClawClass {
    // constant namespace variables
    const inline int armStateArray[3] = {100, 200, 300};
    enum GrabberState {
        CLOSE = 0,
        OPEN = 1
    };

    class claw {
        private:
        // these are variables that can only be acessed by the class
        int angle_target = 0;
        pros::Motor* clawFlipMotor;
        pros::Rotation* clawRotationSensor;
        ez::Piston* clawPisiton;
        ez::PID ClawPID{0.25, 0, 0.08, 0, "Claw"};


        public:
        // contains constructors and methods to interact with claw
        // constructor method, this takes in a motor, rotation sensor and pisiton 
        claw(pros::Motor &ClawMotor, pros::Rotation &ClawRotation, ez::Piston &GrabberPisiton) {
            clawFlipMotor = &ClawMotor;
            clawRotationSensor = &ClawRotation;
            clawPisiton = &GrabberPisiton;
        };
        // inits the claw sensor and PID
        void initalize();
        // updates the claw PID
        void update_pid();
        // controlls opening and closing of claw
        void set_status(GrabberState grabberStatus);
    };
}