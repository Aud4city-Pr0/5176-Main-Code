#pragma once
//-----------------------------------------
// File name: clawarm.hpp
// Creation date: 7/13/26
// Created By: Zach D
// Description: The claw arm mechanism class, contains methods for controling the claw's arm
//-----------------------------------------

// File includes
//--------------------
#include "EZ-Template/PID.hpp"
#include "pros/motors.hpp"
#include "pros/rotation.hpp"
#include "EZ-Template/api.hpp"

// the Claw arm class
namespace ArmClass {
    // the position array, will have data after rotation is plugged into brain
    
    // this is the positionArray, each of its indexes (0 - 5) coresponds to one of its 6 states that it can be in.
    // For example, index 1 of the array corespondes to state 2 (index 1 -> state 2).
    // Here is a list of all of the coresponding indexes and the states/positions that they are assigned to
    // index 0 -> state 1
    // index 1 -> state 2
    // index 2 -> state 3
    // index 3 -> state 4
    // index 4 -> state 5
    // index 5 -> state 6
    const inline int positionArray[6] = {0, 420, 785, 1900, 1400, 850};

    // The arm class
    class arm {
        // contains vars and functions that can only be acessed internally
        private:
        pros::Motor* armMotor;
        pros::Rotation* armRotation;
        ez::PID ArmPID{0.8, 0, 0.08, 0, "Arm"};
        int angle_target = 0;

        // conatains vars and functions that can be acessed publicly by class members or other .cpp file
        public:
        // the constructor function for the arm class, it takes in a motor, rotation sensor
        arm(pros::Motor &clawArmMotor, pros::Rotation &clawArmRotation) {
            armMotor = &clawArmMotor;
            armRotation = &clawArmRotation;
        }

        // this function will move the arm based on an int that ranges from 0-4.
        void move_to_position(int position);
        // initalizer function that sets up motor and sensor
        void initalize();
        // updates pid
        void update_pid();
        // checks to see if we have reached the tartget postion or are around it
        bool is_at_target();
    };
}