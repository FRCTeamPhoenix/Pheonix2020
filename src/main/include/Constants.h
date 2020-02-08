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

// Talon IDs for shooter motors
const int TALON_FLYWHEEL_LEFT = 5;
const int TALON_FLYWHEEL_RIGHT = 6;
const int TALON_SHOOTER_TOP = 7;
const int TALON_SHOOTER_BOTTOM = 8;
const int TALON_LOADER_LEFT = 9;
const int TALON_LOADER_RIGHT = 10;
const int TALON_INTAKE = 11;
const int TALON_INTAKE_TILT = 12;

// Optical Sensor DigitalInput ID
const int INPUT_LOADER_SENSOR = 0;