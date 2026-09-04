//-----------------------------------------
// File name: claw.cpp
// Creation date: 7/28/26
// Created By: Zach D
// Description: The claw mechanism class, contains methods for controling the claw
//-----------------------------------------

// File includes
#include "mechanisums/claw.hpp"
#include "pros/motors.hpp"
#include "pros/rotation.h"
#include "EZ-Template/piston.hpp"
#include "EZ-Template/PID.hpp"
#include "pros/rotation.hpp"
#include "pros/screen.h"
#include "pros/screen.hpp"

// this section will contain the code for the functions
//------------------------------------------------------

// inits the claw and its sensors
void ClawClass::claw::initalize() {
    clawFlipMotor->set_brake_mode(pros::v5::MotorBrake::hold);
    clawFlipMotor->tare_position();
    clawRotationSensor->reset_position();
    ClawPID.exit_condition_set(5, 10);
}

// sets the current target of our pid via the claw status array
void ClawClass::claw::set_claw_position(int position) {
    // setting angle_target
    angle_target = ClawClass::clawStateArray[position];
    // setting PID target
    ClawPID.target_set(angle_target);
}

// updates the pid of the claw
void ClawClass::claw::update_pid() {
    // getting current number of ticks
    int current_ticks = clawFlipMotor->get_position();
    //pros::screen::print(pros::E_TEXT_MEDIUM, 0, "Current ticks claw: %d", current_ticks);
    // computing ouput speed
    double output_speed = ClawPID.compute(current_ticks);
    //pros::screen::print(pros::E_TEXT_MEDIUM, 1, "Current speed %d", output_speed);
    clawFlipMotor->move(output_speed);
}

// sets status of the claw grabber
void ClawClass::claw::set_status(ClawClass::GrabberState grabberState) {
    if(grabberState == ClawClass::GrabberState::CLOSE) {
        claw::clawPisiton->set(true);
    } else if(grabberState == ClawClass::GrabberState::OPEN) {
        claw::clawPisiton->set(false);
    }
}

// this function checks the motor position to see if it is at or around the target position
bool ClawClass::claw::is_at_target() {
    return std::abs(clawFlipMotor->get_position() - angle_target) < 5;
}