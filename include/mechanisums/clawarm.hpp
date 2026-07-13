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
    inline int positionArray[4] = {};

    // The arm class
    class arm {
        // contains vars and functions that can only be acessed internally
        private:
        pros::Motor* armMotor;
        pros::Rotation* armRotation;
        int speed = 0;
        ez::PID ArmPID{0.45, 0, 0, 0, "Arm"};

        // conatains vars and functions that can be acessed publicly by class members or other .cpp file
        public:
        // the constructor function for the arm class, it takes in a motor, rotation sensor, and a speed value from -127 to 127
        arm(pros::Motor &clawArmMotor, pros::Rotation &clawArmRotation, int defaultSpeed) {
            armMotor = &clawArmMotor;
            armRotation = &clawArmRotation;
            speed = defaultSpeed;
        }

        // this function will move the arm based on an int that ranges from 0-4.
        void move_to_position(int position);
        // initalizer function that sets up motor and sensor
        void initalize();
    };
}