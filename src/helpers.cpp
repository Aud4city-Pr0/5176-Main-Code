//-----------------------------------------
// File name: helpers.cpp
// Creation date: 6/12/26
// Created By: Zach D
// Description: Contains some helper functions for the robot
//-----------------------------------------

// helper variables
//------------------
int positionState = 0;
int postionStateClaw = 0;
bool graberActive = false;
bool waitForArm = false;

// helper constant variables
//----------------------------
const int MAX_STATE = 4;
const int MAX_STATE_CLAW = 3;

// includes
//-----------
#include "mechanisums/intake.hpp"
#include "mechanisums/lift.hpp"
#include "mechanisums/claw.hpp"
#include "pros/misc.h"
#include "pros/rotation.hpp"
#include "pros/screen.h"
#include "helpers.hpp"
#include "subsystems.hpp"
#include "EZ-Template/util.hpp"

// conversion functions
int get_rotation_value(pros::Rotation rotSensor) {
    int converted_val = rotSensor.get_angle() / 100;
    //pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Current rotation %d", converted_val);
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
    botClawArm.initalize();
    botClaw.initalize();
}

void pid_task() {
    while (true) {
        botClawArm.update_pid();
        botClaw.update_pid();
        botLift.update_pid();
        pros::delay(10);
    }
}

void driver_control_arm() {
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
        // incrementing by one every time when button is pressed  
        positionState++;
        // preventing postionState from going outside of array index
        if (positionState >= MAX_STATE) {
            positionState = 0;
        }
        
        // incrementing claw state
        postionStateClaw++;
        // preventing postionStateClaw from going outside of array index
        if (postionStateClaw >= MAX_STATE_CLAW) {
            postionStateClaw = 0;
        }
        // calling the arm position function
        botClawArm.move_to_position(positionState);

        // setting waitForArm to true
        waitForArm = true;

    }

    // runing after arm movement has completed
    if(waitForArm && botClawArm.is_at_target()) {
        botClaw.set_claw_position(postionStateClaw);
        waitForArm = false;
    }
}

void driver_controll_claw() {
    // if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        // incrementing by 1
        //postionStateClaw++;
        // preventing state from going out of array
        //if(postionStateClaw >= MAX_STATE_CLAW) {
            //postionStateClaw = 0;
        //}
        // for debugging
        // pros::screen::print(pros::E_TEXT_MEDIUM, 5, "Current position %d", positionStateClaw) 
    //} 
    // clawing claw postion function
    //botClaw.set_claw_position(postionStateClaw);

    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        graberActive = !graberActive;
    }

    if(graberActive) {
        botClaw.set_status(ClawClass::GrabberState::CLOSE);
    } else {
        botClaw.set_status(ClawClass::GrabberState::OPEN);
    }
}