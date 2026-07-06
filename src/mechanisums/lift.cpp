//-----------------------------------------
// File name: lift.cpp
// Creation date: 7/6/26
// Created By: Zach D
// Description: The lift mechanism class, contains methods for controling lift and doing distance calculations with distance sensor
//-----------------------------------------

// includes
//--------------
#include "mechanisums/lift.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/motors.hpp"

// the class helpers function code
void LiftClass::lift::move_lift_with_status(liftState state) {
    // checking to see if state is equal to LOWER
    if(state == liftState::LOWER) {
        // if state is LOWER, then reverse the motor to spin down and run at default speed
        lift::liftMotor->set_reversed(true);
        lift::liftMotor->move_voltage(lift::defaultSpeed);
        // checking to see if state is equal to RAISE
    } else if (state == liftState::RAISE) {
        // if state is RAISE, then don't reverse the motor to spin up and run at default speed
        lift::liftMotor->set_reversed(false);
        lift::liftMotor->move_voltage(lift::defaultSpeed);
    } else if(state == liftState::STOP) {
        // stoping motor if state is set to STOP
        lift::liftMotor->brake();
    }
}

void LiftClass::lift::move_lift_with_pid(int height) {
    //TODO: implement pid and distance sensor code when distance sensor arrives.
}

void LiftClass::lift::init_lift() {
    // initalizes lift motor, pid and sensors
    // setting lift braking to hold so that we can keep our position
    lift::liftMotor->set_brake_mode(pros::MotorBrake::hold);
}