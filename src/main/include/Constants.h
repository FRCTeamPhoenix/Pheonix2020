/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/I2C.h>
#include <frc/util/Color.h>

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
const int TALON_FRONT_LEFT = 4;
const int TALON_BACK_LEFT = 3;
const int TALON_FRONT_RIGHT = 1;
const int TALON_BACK_RIGHT = 2;

//ids for the talons
const int IMU_ID = 0;

//ids for the solenoids
const int PCM_CAN_ID = 11;
const int SOLENOID_HIGH_GEAR = 6;
const int SOLENOID_LOW_GEAR = 7;

//ports for sensors
const auto COLOR_SENSOR_PORT = frc::I2C::Port::kOnboard;
const frc::Color BLUE_TARGET = frc::Color(0.143, 0.427, 0.429);
const frc::Color GREEN_TARGET = frc::Color(0.197, 0.561, 0.240);
const frc::Color RED_TARGET = frc::Color(0.561, 0.232, 0.114);
const frc::Color YELLOW_TARGET = frc::Color(0.361, 0.524, 0.113);

//slots for the two different pid configs on talons
const int PID_VELOCITY_SLOT = 0;
const int PID_HEADING_SLOT = 1;

//used for the aim adjust
const double AIM_P = 0.05;
const double AIM_DIST_P = 0.03;
const double AIM_FF = 0.01;
const double AIM_THRESH = 0.5;
const double DIST_TRESH = 5.0;

//used for the turning maneuver
const double TURN_P = 0.02;
const double TURN_FF = 0.01;
const double TURN_THRESH = 10.0;
const double TURN_END_TRESH = 5;

//info about the target and camera for distance calculations
const double TARGET_HEIGHT_IN = 48.0;
const double CAMERA_HEIGHT_IN = 7.5;
const double CAMERA_ANGLE = 0.0;
const double TARGET_DIST_IN = 240.0;

//conversion values
const double TICKS_PER_REV = 4096.0;
const double TICKS_PER_IMU_ROTATION = 8192.0;
const double WHEEL_DIMATER_IN = 6;
const double DRIVE_TRAIN_WIDTH_IN = 26;
const double PI = 3.1415;
const double ROTATIONS_TO_DISTANCE = WHEEL_DIMATER_IN * PI;
const double TICKS_TO_DISTANCE = ROTATIONS_TO_DISTANCE / TICKS_PER_REV;