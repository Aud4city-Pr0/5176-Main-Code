//-----------------------------------------
// File name: helpers.cpp
// Creation date: 6/12/26
// Created By: Zach D
// Description: Contains some helper functions for the robot
//-----------------------------------------

// includes
//-----------
#include "mechanisums/intake.hpp"
#include "mechanisums/lift.hpp"
#include "pros/misc.h"
#include "pros/rotation.hpp"
#include "pros/screen.h"
#include "helpers.hpp"
#include "subsystems.hpp"
#include "EZ-Template/util.hpp"

// conversion functions
int get_rotation_value(pros::Rotation rotSensor) {
    int converted_val = rotSensor.get_angle() / 100;
    pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Current rotation %d", converted_val);
    return converted_val;
}

// helper functions for driver and auto
void driver_control_intake() {
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        botIntake.set_intake_direction(IntakeClass::FORWARD);
        botIntake.set_status(true);
    } else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        botIntake.set_intake_direction(IntakeClass::BACKAWRD);
        botIntake.set_status(true);
    } else {
        botIntake.set_status(false);
    }
}

void driver_control_lift() {
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        botLift.move_lift_with_status(LiftClass::liftState::RAISE);
    } else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        botLift.move_lift_with_status(LiftClass::liftState::LOWER);
    } else {
        botLift.move_lift_with_status(LiftClass::liftState::STOP);
    }
}

void init_the_bot() {
    botLift.initalize();
}