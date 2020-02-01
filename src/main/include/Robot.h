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
#include <frc2/command/SequentialCommandGroup.h>

#include "commands/MotionProfile.h"
#include "commands/DefaultDrive.h"
#include "commands/AimAdjust.h"

#include "ColorSensor.h"

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
  DefaultDrive m_defaultDrive;
  frc::Joystick m_driverJoystick{0};
  AimAdjust m_nonAutoAim{false};
  frc2::SequentialCommandGroup m_autoCommand{MotionProfile(), AimAdjust(true)};

  bool m_buttonPressed = false;
  int m_counter = 0;

  ColorSensor m_colorSensor;
};
