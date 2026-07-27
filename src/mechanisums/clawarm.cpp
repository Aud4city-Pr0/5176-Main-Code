//-----------------------------------------
// File name: clawarm.hpp
// Creation date: 7/13/26
// Created By: Zach D
// Description: The claw arm mechanism class, contains methods for controling the claw's arm
//-----------------------------------------

// File includes
//--------------------
#include "mechanisums/clawarm.hpp"
#include "EZ-Template/PID.hpp"
#include "EZ-Template/util.hpp"
#include "pros/motors.hpp"
#include "pros/rotation.hpp"
#include "EZ-Template/api.hpp"
#include "helpers.hpp"
#include "pros/rtos.hpp"
#include "pros/screen.h"
#include "subsystems.hpp"

// this contains all of the function code

// this function will move the arm based on an int that ranges from 0-4.
void ArmClass::arm::move_to_position(int position) {
    // getting angle from array index
    angle_target = positionArray[position] 
    //pros::screen::print(
    //pros::E_TEXT_MEDIUM,
    //0,
    //"Index: %d Target: %d",
    //position,
    //angle_target
    //);
    // setting pid
    ArmPID.target_set(angle_target);

}

void ArmClass::arm::update_pid() {
    // getting angle
    int current_angle = armMotor->get_position();
    // caculating ouput
    double output = ArmPID.compute(current_angle);
    //pros::screen::print(pros::E_TEXT_MEDIUM, 0, "Angle: %d", current_angle);
   //pros::screen::print(
        //pros::E_TEXT_MEDIUM,
        //3,
        //"Angle: %d",
        //current_angle

    //);
    //pros::screen::print(pros::E_TEXT_MEDIUM, 4, "Output: %d", output);
    // moving arm motor
    armMotor->move(output);
}

// this function inits the sensors, pid and motor
void ArmClass::arm::initalize() {
    armMotor->set_brake_mode(pros::v5::MotorBrake::hold);
    armMotor->tare_position();
    armRotationSensor.reset_position();
    ArmPID.exit_condition_set(5, 10);
}

