/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/kinematics/DifferentialDriveKinematics.h>

/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */
//ids for the talons
const int TALON_MASTER_LEFT = 3;
const int TALON_SLAVE_LEFT = 4;
const int TALON_MASTER_RIGHT = 1;
const int TALON_SLAVE_RIGHT = 2;

//ids for the solenoids
const int PCM_CAN_ID = 11;
const int SOLENOID_HIGH_GEAR = 6;
const int SOLENOID_LOW_GEAR = 7;

//slots for the two different pid configs on talons
const int PID_VELOCITY_SLOT = 0;
const int PID_DISTANCE_SLOT = 1;

//values for the auto trajectory
const auto MAX_SPEED = 12_fps;
const auto MAX_ACCELERATION = 3 * 1_fps / 1_s;
const auto TRACK_WIDTH = 24_in;

//from characterization
const auto kS = 1.39_V;
const auto kV = 0.185 * 1_V * 1_s / 1_m;
const auto kA = 0.0242 * 1_V * 1_s * 1_s / 1_m;

//parameters for the ramsete loop
const double RAMSETE_B = 2;
const double RAMSETE_ZETA = 0.7;

//a kinematics object for drivetrain calculations
const frc::DifferentialDriveKinematics DRIVE_KINEMATICS{TRACK_WIDTH};

//conversion factors from feet to encoder ticks
const auto WHEEL_DIAMETER_IN = 6;
const int TICKS_PER_REV = 4096;

const auto TICKS_TO_DISTANCE_FT = WHEEL_DIAMETER_IN * 3.1415 / TICKS_PER_REV * 2.54 / 100;