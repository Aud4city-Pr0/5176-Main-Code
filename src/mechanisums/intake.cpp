//-----------------------------------------
// File name: intake.cpp
// Creation date: 6/23/26
// Created By: Zach D
// Description: The intake mechanism class, contains methods for controling intake
//-----------------------------------------

// includes
//--------------
#include "mechanisums/intake.hpp"
#include "pros/motors.hpp"


// the class helpers function code
void IntakeClass::intake::set_status(bool intakeStatus) {
    if(intakeStatus == true) {
        IntakeClass::intake::motorA->move_voltage(IntakeClass::intake::defaultSpeed);
        IntakeClass::intake::motorB->move_voltage(IntakeClass::intake::defaultSpeed);
        IntakeClass::intake::counterMotor->move_voltage(IntakeClass::intake::defaultSpeed);
    } else if(intakeStatus == false) {
        IntakeClass::intake::motorA->brake();
        IntakeClass::intake::motorB->brake();
        IntakeClass::intake::counterMotor->brake();
    }
}

void IntakeClass::intake::set_status(bool intakeStatus, int speed) {
    if(intakeStatus == true) {
        IntakeClass::intake::motorA->move_voltage(speed);
        IntakeClass::intake::motorB->move_voltage(speed);
        IntakeClass::intake::counterMotor->move_voltage(speed);
    } else if(intakeStatus == false) {
        IntakeClass::intake::motorA->brake();
        IntakeClass::intake::motorB->brake();
        IntakeClass::intake::counterMotor->brake();
    }
}

void IntakeClass::intake::set_intake_direction(IntakeClass::Direction intakeDir) {
    if(intakeDir == IntakeClass::FORWARD) {
        IntakeClass::intake::motorA->set_reversed(false);
        IntakeClass::intake::motorB->set_reversed(false);
        IntakeClass::intake::counterMotor->set_reversed(true);
    } else if (intakeDir == IntakeClass::BACKAWRD) {
        IntakeClass::intake::motorA->set_reversed(true);
        IntakeClass::intake::motorB->set_reversed(true);
        IntakeClass::intake::counterMotor->set_reversed(false);
    }
}