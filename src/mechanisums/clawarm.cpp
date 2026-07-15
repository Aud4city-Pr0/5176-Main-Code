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

// this contains all of the function code

// this function will move the arm based on an int that ranges from 0-4.
void ArmClass::arm::move_to_position(int position) {
    // getting angle from array index
    angle_target = ArmClass::positionArray[position];
    // seting PID target
    ArmPID.target_set(angle_target);
    // preforming computation
    while (true){
        // converting again so that we can have an updated value
        int converted_angle = get_rotation_value(*armRotation);
        // caclulating motor speed output
        double outputSpeed = ArmPID.compute(converted_angle);
        // Exit when close enough to target
        if (abs(angle_target - converted_angle) < 5) {
            break;
        }
        // moving the motor
        armMotor->move(outputSpeed);
        // wating for task to complete
        pros::delay(ez::util::DELAY_TIME);
    }
    armMotor->move(0);

}

// this function inits the sensors, pid and motor
void ArmClass::arm::initalize() {
    armMotor->set_brake_mode(pros::v5::MotorBrake::hold);
    armRotation->reset_position();
    armMotor->tare_position();
    ArmPID.exit_condition_set(5, 10);
}

