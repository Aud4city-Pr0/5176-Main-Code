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
    angle_target = positionArray[position];
    ArmPID.target_set(angle_target);

}

void ArmClass::arm::update_pid() {
    // getting angle
    int current_angle = armMotor->get_position();
    // caculating ouput
    double output = ArmPID.compute(current_angle);
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

// this function checks the motor position to see if it is at or around the target position
bool ArmClass::arm::is_at_target() {
    return std::abs(armMotor->get_position() - angle_target) < 10;
}

