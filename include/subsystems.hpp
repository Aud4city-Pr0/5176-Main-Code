#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"
#include "pros/rotation.hpp"

extern Drive chassis;

// Your motors, sensors, etc. should go here.  Below are examples

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');
inline pros::Rotation testRotation(15);