#include "main.h"
//-----------------------------------------
// File name: helpers.cpp
// Creation date: 6/12/26
// Created By: Zach D
// Description: Contains some helper functions for the robot
//-----------------------------------------

// includes
//-----------
#include "pros/rotation.hpp"
#include "pros/screen.h"
#include "helpers.hpp"
#include "pros/motors.hpp"
#include "mechanisums/intake.hpp"

// conversion functions
void print_rot_value(pros::Rotation rotSensor) {
    int converted_val = rotSensor.get_angle() / 100;
    if(converted_val == 360) {
        // resets rotation sensor
        rotSensor.reset_position();
    }
    pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Current rotation %d", converted_val);
}

// helper functions for driver and auto

// contains 
void driver_control_intake() {
    // code
}