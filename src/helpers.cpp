
#include "main.h"
#include "pros/rotation.hpp"
#include "pros/screen.h"
#include "helpers.hpp"
//-----------------------------------------
// File name: helpers.cpp
// Creation date: 6/12/26
// Created By: Zach D
// Description: Contains some helper functions for the robot
//-----------------------------------------

void print_rot_value(pros::Rotation rotSensor) {
    int converted_val = rotSensor.get_angle() / 100;
    if(converted_val == 360) {
        // resets rotation sensor
        rotSensor.reset_position();
    }
    // pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Current rotation %d", converted_val);
}