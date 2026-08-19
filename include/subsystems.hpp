#pragma once

#include "EZ-Template/api.hpp"
#include "EZ-Template/piston.hpp"
#include "api.h"
#include "pros/abstract_motor.hpp"
#include "pros/rotation.hpp"
#include "pros/motors.hpp"
#include "mechanisums/intake.hpp"
#include "mechanisums/lift.hpp"
#include "mechanisums/clawarm.hpp"
#include "mechanisums/claw.hpp"
extern Drive chassis;

// Your motors, sensors, etc. should go here.  Below are examples

// sensors
inline pros::Rotation armRotationSensor(15);
inline pros::Rotation clawRotationSensor(16);

// motors
inline pros::Motor intakeA(18, pros::v5::MotorGears::green);
inline pros::Motor intakeB(19, pros::v5::MotorGears::green);
inline pros::Motor mainMotorLift(11, pros::v5::MotorGears::green);
inline pros::Motor mainArmMotor(-12, pros::v5::MotorGears::green);
inline pros::Motor mainClawMotor(13, pros::v5::MotorGears::green);

// pnematics
inline ez::Piston clawPisiton('a', false);

// mechansiums
inline IntakeClass::intake botIntake(intakeA, intakeB, 10000);
inline LiftClass::lift botLift(mainMotorLift, 12000, 1270);
inline ArmClass::arm botClawArm(mainArmMotor, armRotationSensor);
inline ClawClass::claw botClaw(mainClawMotor, clawRotationSensor, clawPisiton);