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
    const inline int positionArray[4] = {0, 500, 1100, 1700};

    // The arm class
    class arm {
        // contains vars and functions that can only be acessed internally
        private:
        pros::Motor* armMotor;
        pros::Rotation* armRotation;
        ez::PID ArmPID{0.25, 0, 0.08, 0, "Arm"};
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