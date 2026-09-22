#pragma once
#include "pros/rotation.hpp"
//-----------------------------------------
// File name: helpers.hpp
// Creation date: 6/12/26
// Created By: Zach D
// Description: Contains some helper functions for the robot
//-----------------------------------------

// scoring state enum
enum ScoreState {
    DEFAULT = 0,
    MATCHLOAD = 1,
    MATCHLOAD_MED = 2,
    MATCHLOAD_HIGH = 3,
    SCORE = 4,
    SCORE_HIGH = 5
};

extern bool waitForArm;
extern bool waitForClaw;

// init function for sensors and motors
void init_the_bot();

// returns current value of rotation sensor and divide it by 100 to convert it to normal degrees (eg. 36000/100 -> 360)
int get_rotation_value(pros::Rotation rotSensor);

// contains the driver conrtol code for intake
void driver_control_intake();

// contains the driver control code for lift
void driver_control_lift();

// arm task
void pid_task();

// contains the driver control code for the claw arm
void driver_control_arm();

// method for moving arm and claw in auto via one line of code
void set_scoring_to(ScoreState score);