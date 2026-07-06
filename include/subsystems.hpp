#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"
#include "pros/abstract_motor.hpp"
#include "pros/rotation.hpp"
#include "pros/motors.hpp"
#include "mechanisums/intake.hpp"
#include "mechanisums/lift.hpp"
extern Drive chassis;

// Your motors, sensors, etc. should go here.  Below are examples

// sensors
inline pros::Rotation testRotation(15);

// motors for intake
inline pros::Motor intakeA(8, pros::v5::MotorGears::green);
inline pros::Motor intakeB(9, pros::v5::MotorGears::green);

// motors for lift
inline pros::Motor mainMotorLift(10, pros::v5::MotorGears::green);

// mechansiums
inline IntakeClass::intake botIntake(intakeA, intakeB, 10000);
inline LiftClass::lift botLift(mainMotorLift, 12000);