#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"
#include "pros/rotation.hpp"
#include "pros/motors.hpp"
#include "mechanisums/intake.hpp"

extern Drive chassis;

// Your motors, sensors, etc. should go here.  Below are examples

// sensors
inline pros::Rotation testRotation(15);

// motors
inline pros::Motor intakeA(8);
inline pros::Motor intakeB(9);

// mechansiums
inline IntakeClass::intake botIntake(intakeA, intakeB, 10000);