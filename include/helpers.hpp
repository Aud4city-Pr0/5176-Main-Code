#pragma once
#include "pros/rotation.hpp"
//-----------------------------------------
// File name: helpers.hpp
// Creation date: 6/12/26
// Created By: Zach D
// Description: Contains some helper functions for the robot
//-----------------------------------------

// prints out current value of rotation sensor and divide it by 100 to convert it to normal degrees (eg. 36000/100 -> 360)
// TODO: rewrite to return int and do math with a rotation sensor group class
void print_rot_value(pros::Rotation rotSensor);

// contains the driver conrtol code for intake
void driver_control_intake();