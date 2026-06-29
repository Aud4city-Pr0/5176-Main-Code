#pragma once
//-----------------------------------------
// File name: intake.hpp
// Creation date: 6/23/26
// Created By: Zach D
// Description: The intake mechanism class, contains methods for controling intake
//-----------------------------------------

// includes
//-------------
#include "pros/motors.hpp"

// intake class
namespace IntakeClass {

    // intake direction enum
    enum Direction {
        FORWARD = 0,
        BACKAWRD = 1
    };

    class intake {
        // interal class variables or functions that are not messed with by other classes or code in main
        private:
        int defaultSpeed = 0;
        pros::Motor* motorA;
        pros::Motor* motorB;

        // external variables or functions that can be used or changed by other classes or code in main
        public:
        // initalizer/constructor function that creates a intake object by taking in three motors and a default speed
        intake(pros::Motor &inkateMotorA, pros::Motor &intakeMotorB,  int intakeDefaultSpeed) {
            motorA = &inkateMotorA;
            motorB = &intakeMotorB;
            defaultSpeed = intakeDefaultSpeed;
        }

        // void function that turns intake on and off using a boolean true/false value
        void set_status(bool intakeStatus);
        // variation of set_status that overrides the defaultSpeed variable to allow for a custom speed that ranges between -12000 and 12000 millivolts
        void set_status(bool intakeStatus, int speed);
        // setter function that controlls direction of intake using enums
        void set_intake_direction(Direction intakeDir);
    };
};