/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

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

//ids for the solenoids
const int PCM_CAN_ID = 11;
const int SOLENOID_HIGH_GEAR = 6;
const int SOLENOID_LOW_GEAR = 7;

//slots for the two different pid configs on talons
const int PID_VELOCITY_SLOT = 0;
const int PID_HEADING_SLOT = 1;

//used for the aim adjust
const float AIM_P = 0.05f;
const float AIM_DIST_P = 0.04f;
const float AIM_FF = 0.01f;
const float AIM_THRESH = 0.5f;

//info about the target and camera for distance calculations
const float TARGET_HEIGHT_IN = 33.0f;
const float CAMERA_HEIGHT_IN = 7.5f;
const float CAMERA_ANGLE = 0.0f;
const float TARGET_DIST_IN = 100.0f;

//conversion values
const float TICKS_PER_REV = 4096.0f;
const float WHEEL_DIMATER_IN = 6;
const float PI = 3.1415;
const float TICKS_TO_DISTANCE = WHEEL_DIMATER_IN * PI / TICKS_PER_REV;