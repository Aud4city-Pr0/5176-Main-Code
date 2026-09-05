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
bool waitForClaw = false;

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
        // bumper switch acts as an autostop
        // inverting get_value because of the switch possibly using a pullup resistor
    } else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2) && !liftBumper.get_value()) {
        botLift.move_lift_with_status(LiftClass::liftState::LOWER);
    } else {
        botLift.move_lift_with_status(LiftClass::liftState::STOP);
    }

    if(liftBumper.get_value() == 0) {
        botLift.liftMotor->set_brake_mode(pros::MotorBrake::coast);
    } else {
        botLift.liftMotor->set_brake_mode(pros::MotorBrake::hold);
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
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        // setting arm and claw to position zero
        positionState = 0;
        postionStateClaw = 0;
        botClaw.set_claw_position(postionStateClaw);

        // setting waitForArm to true
        waitForClaw = true;

    } else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
        // setting arm and claw to position zero
        positionState = 1;
        postionStateClaw = 1;
        botClawArm.move_to_position(positionState);

        // setting waitForArm to true
        waitForArm = true;
    } else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
        // setting arm and claw to position zero
        positionState = 2;
        postionStateClaw = 2;
        botClawArm.move_to_position(positionState);

        // setting waitForArm to true
        waitForArm = true;
    } else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
        // setting arm and claw to position zero
        positionState = 3;
        postionStateClaw = 3;
        botClawArm.move_to_position(positionState);

        // setting waitForArm to true
        waitForArm = true;
    } else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
        // setting arm and claw to position zero
        positionState = 4;
        postionStateClaw = 4;
        botClawArm.move_to_position(positionState);

        // setting waitForArm to true
        waitForArm = true;
    } else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
       // setting arm and claw to position zero
        positionState = 5;
        postionStateClaw = 5;
        botClawArm.move_to_position(positionState);

        // setting waitForArm to true
        waitForArm = true;  
    }

    // runing after arm movement has completed
    if(waitForArm && botClawArm.is_at_target()) {
        botClaw.set_claw_position(postionStateClaw);
        waitForArm = false;
    }

    // runing after claw movemnet has finished
    if(waitForClaw && botClaw.is_at_target()) {
        botClawArm.move_to_position(positionState);
        waitForClaw = false;
    }
}

void driver_controll_claw() {

    // checks for a button press as soon as one happens
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        // flips bool variable value to oppostite value (eg. true -> false and false -> true)
        graberActive = !graberActive;
    }

    if(graberActive) {
        botClaw.set_status(ClawClass::GrabberState::CLOSE);
    } else {
        botClaw.set_status(ClawClass::GrabberState::OPEN);
    }
}