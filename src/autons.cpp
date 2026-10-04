#include "main.h"
#include "pros/device.hpp"
#include "pros/rtos.hpp"
#include "subsystems.hpp"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 110;


// includes for the mechanisums
#include "mechanisums/lift.hpp"
#include "mechanisums/intake.hpp"
#include "mechanisums/claw.hpp"
#include "mechanisums/clawarm.hpp"
#include "helpers.hpp"
///
// Constants
///
void default_constants() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(20.0, 0.0, 100.0);         // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(11.0, 0.0, 20.0);        // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(3.0, 0.05, 20.0, 15.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
  chassis.pid_odom_angular_constants_set(6.5, 0.0, 52.5);    // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions

  // Exit conditions
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.9);

  chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
}

// Robot autos
// this section will contain all of our autos like match auto (15 second), alternate match auto (15 second), elim auto (15 second) and skills (60 second)

// Competion autos
// red side autos
void left_side_auto() {
  // enabling lift pid
  botLift.enable_pid();
  // driving out before turn
  chassis.pid_drive_set(15_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();
  // moving claw and arm
  set_scoring_to(SCORE);
  pros::delay(500);
  // driving to score
  chassis.pid_drive_set(-17.8_in, 85);
  chassis.pid_wait();
  botClaw.set_status(ClawClass::GrabberState::OPEN);
  botIntake.set_status(false);
  // driving to get first angled pin
  botLift.move_lift_with_pid(3300);
  pros::delay(990);
  chassis.pid_drive_set(9.5_in, DRIVE_SPEED);
  chassis.pid_wait();
  set_scoring_to(SCORE, 450);
  chassis.pid_turn_set(213_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-21.7_in, 48);
  chassis.pid_wait();
  botLift.move_lift_with_pid(0);
  pros::delay(1300);
  botClaw.set_status(ClawClass::GrabberState::CLOSE);
  botLift.move_lift_with_pid(5700);
  chassis.pid_drive_set(23_in, 75);
  chassis.pid_wait();
  chassis.pid_turn_set(-88_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-10_in, 40);
  chassis.pid_wait();
  pros::delay(350);
  // scoring the cup and pin
  botClaw.set_status(ClawClass::GrabberState::OPEN);
  pros::delay(350);
  // driving back to roller
  botLift.move_lift_with_pid(0);
  chassis.pid_drive_set(12_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();
  // roller time (gambling I LOVE GAMMBLING LETS GOO GAMBLING)
  chassis.pid_drive_set(15_in, DRIVE_SPEED);
  chassis.pid_wait_quick();
  chassis.pid_drive_set(-7_in, DRIVE_SPEED);
  chassis.pid_wait_quick();
  chassis.pid_drive_set(15_in, DRIVE_SPEED);
  chassis.pid_wait_quick();
  chassis.pid_drive_set(-10_in, DRIVE_SPEED);
  chassis.pid_wait_quick();
  set_scoring_to(DEFAULT);

}

void bottom_side_auto() {
  // code here
}

// alternate red side autos
void left_side_alt_auto() {
  // code here
}

void bottom_side_alt_auto() {
  // code here
}

// blue side autos
void right_side_auto() {
  // code here
}

void top_side_auto() {
  // code here
}

// alternate blue side autos
void right_side_alt_auto() {
  // code here
}

void top_side_alt_auto() {
  // code here
}

//TODO: add elim autos for red and blue later

// skills 
void skills_auto() {
  // diriving to red podium
  botClaw.set_status(ClawClass::GrabberState::CLOSE);
  set_scoring_to(SCORE);
  chassis.pid_drive_set(-3.5_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_set(-55_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-8.2_in, DRIVE_SPEED);
  chassis.pid_wait();
  botClaw.set_status(ClawClass::GrabberState::OPEN);
  pros::delay(400);
  botLift.move_lift_with_pid(3300);
  // getting a pin and cup to the left
  set_scoring_to(SCORE, 450);
  chassis.pid_drive_set(9.75_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_set(40_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-7_in, DRIVE_SPEED);
  chassis.pid_wait();
}