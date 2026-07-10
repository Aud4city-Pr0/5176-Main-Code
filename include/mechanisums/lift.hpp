#pragma once
//-----------------------------------------
// File name: lift.hpp
// Creation date: 7/6/26
// Created By: Zach D
// Description: The lift mechanism class, contains methods for controling lift and doing distance calculations with distance sensor
//-----------------------------------------

// includes
//-------------
#include "pros/motors.hpp"

// lift class
namespace LiftClass {
    // lift status enums
    enum liftState {
        LOWER = 0,
        RAISE = 1,
        STOP = 2
    };

    class lift {
        // interal class variables or functions that are only used inside the class.
        private:
        pros::Motor* liftMotor;
        int defaultSpeed = 0;

        // external variables or functions that can be used or changed by other classes or code in main.
        public:
        // initalizer/constructor function that creates a intake object by taking in one motor and a default speed.
        lift(pros::Motor &mainLiftMotor, int speed) {
            //TODO: add distance sensor parameter
            liftMotor = &mainLiftMotor;
            defaultSpeed = speed;
        }
        // sets up our lift sensors and motor breaking, MUST CALL FIRST BEFORE ANY OTHER LIFT CLASS FUNCTION IN MAIN. DON'T REMOVE!!!!
        void initalize();
        // moves lift with the liftState enum and not the lift pid+distance sensor.
        void move_lift_with_status(liftState status);
        // move lift with pid and distance sensor to a height in milimeters.
        //TODO: add distance sensor and pid, this function will currently be unusable in the meantime untill then.
        void move_lift_with_pid(int height);
    };
}