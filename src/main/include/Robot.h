/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/Command.h>
#include <frc/Joystick.h>

#include "commands/MotionProfile.h"
#include "commands/DefaultDrive.h"
#include "commands/AimAdjust.h"

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;

private:
  MotionProfile m_profile;
  DefaultDrive m_defaultDrive;
  frc::Joystick m_driverJoystick{0};
};
