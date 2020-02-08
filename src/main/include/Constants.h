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

// Talon IDs
const int TALON_FRONT_LEFT = 1;
const int TALON_FRONT_RIGHT = 2;
const int TALON_BACK_LEFT = 3;
const int TALON_BACK_RIGHT = 4;
const int TALON_FLYWHEEL_LEFT = 5;
const int TALON_FLYWHEEL_RIGHT = 6;
const int TALON_SHOOTER_TOP = 7;
const int TALON_SHOOTER_BOTTOM = 8;
const int TALON_LOADER_LEFT = 9;
const int TALON_LOADER_RIGHT = 10;
const int TALON_INTAKE = 11;
const int TALON_INTAKE_TILT = 12;

// Solenoid IDs
const int PCM_CAN_ID = 11;
const int SOLENOID_HIGH_GEAR = 6;
const int SOLENOID_LOW_GEAR = 7;

// Sensor ports
const int INPUT_LOADER_SENSOR = 0;
const auto COLOR_SENSOR_PORT = frc::I2C::Port::kOnboard;
const frc::Color BLUE_TARGET = frc::Color(0.143, 0.427, 0.429);
const frc::Color GREEN_TARGET = frc::Color(0.197, 0.561, 0.240);
const frc::Color RED_TARGET = frc::Color(0.561, 0.232, 0.114);
const frc::Color YELLOW_TARGET = frc::Color(0.361, 0.524, 0.113);

// Slots for the two different pid configs on talons
const int PID_VELOCITY_SLOT = 0;
const int PID_HEADING_SLOT = 1;

// Used for the aim adjust
const float AIM_P = 0.05f;
const float AIM_DIST_P = 0.04f;
const float AIM_FF = 0.01f;
const float AIM_THRESH = 0.5f;

// Info about the target and camera for distance calculations
const float TARGET_HEIGHT_IN = 33.0f;
const float CAMERA_HEIGHT_IN = 7.5f;
const float CAMERA_ANGLE = 0.0f;
const float TARGET_DIST_IN = 100.0f;

// Conversion values
const float TICKS_PER_REV = 4096.0f;
const float WHEEL_DIMATER_IN = 6;
const float PI = 3.1415;
const float TICKS_TO_DISTANCE = WHEEL_DIMATER_IN * PI / TICKS_PER_REV;
