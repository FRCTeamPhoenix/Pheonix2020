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
const int TALON_FRONT_LEFT = 3;
const int TALON_BACK_LEFT = 4;
const int TALON_FRONT_RIGHT = 1;
const int TALON_BACK_RIGHT = 2;

//ids for the solenoids
const int PCM_CAN_ID = 11;
const int SOLENOID_HIGH_GEAR = 6;
const int SOLENOID_LOW_GEAR = 7;


//slots for the two different pid configs on talons
const int PID_VELOCITY_SLOT = 0;
const int PID_DISTANCE_SLOT = 1;