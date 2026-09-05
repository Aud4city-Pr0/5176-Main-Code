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
#include "EZ-Template/piston.hpp"
#include "EZ-Template/PID.hpp"
#include "pros/rotation.hpp"

// the claw class
namespace ClawClass {
    // constant namespace variables

    // this is the clawSateArray, each of its indexes (0 - 5) coresponds to one of its 6 states that it can be in.
    // For example, index 1 of the array corespondes to state 2 (index 1 -> state 2).
    // Here is a list of all of the coresponding indexes and the states/positions that they are assigned to
    // index 0 -> state 1
    // index 1 -> state 2
    // index 2 -> state 3
    // index 3 -> state 4
    // index 4 -> state 5
    // index 5 -> state 6
    const inline int clawStateArray[6] = {50, -1100, -900, -300, 250, -150};
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
        ez::PID ClawPID{0.55, 0, 0.08, 0, "Claw"};


        public:
        // contains constructors and methods to interact with claw
        // constructor method, this takes in a motor, rotation sensor and pisiton 
        claw(pros::Motor &ClawMotor, pros::Rotation &ClawRotation, ez::Piston &GrabberPisiton) {
            clawFlipMotor = &ClawMotor;
            clawRotationSensor = &ClawRotation;
            clawPisiton = &GrabberPisiton;
        };
        // sets the claw postion from the claw state array
        void set_claw_position(int postion);
        // inits the claw sensor and PID
        void initalize();
        // updates the claw PID
        void update_pid();
        // controlls opening and closing of claw
        void set_status(GrabberState grabberStatus);
        // checks to see if claw is at target
        bool is_at_target();
    };
}