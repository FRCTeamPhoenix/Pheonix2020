/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>
#include <frc2/command/button/JoystickButton.h>
#include "subsystems/TankSubsystem.h"
#include "PCMHandler.h"

#include "ControlBinding.h"
#include "Shooter.h"

void Robot::RobotInit() {
    ControlBinding::getInstance()->initialize();
    TankSubsystem::getInstance()->init();
    TankSubsystem::getInstance()->zeroEncoders();
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() { 
    frc2::CommandScheduler::GetInstance().Run();
    TankSubsystem::getInstance()->updateGyro();

    //update color sensor values
    frc::Color detectedColor = m_colorSensor.getDetectedColor();
    std::string approxColor = m_colorSensor.getApproximateColor();

    frc::SmartDashboard::PutNumber("R", detectedColor.red);
    frc::SmartDashboard::PutNumber("G", detectedColor.green);
    frc::SmartDashboard::PutNumber("B", detectedColor.blue);
    frc::SmartDashboard::PutString("Detected Color", approxColor);
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit() {
}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
    //make robot stop
    TankSubsystem::getInstance()->setSpeed(0.0, 0.0);

    //use a lambda to fix a bug
    frc2::Button button{[&] { return m_driverJoystick.GetRawButton(1); }};

    button.WhenPressed(AimAdjust()).CancelWhenPressed(&m_defaultDrive).WhenReleased(&m_defaultDrive);
    frc2::CommandScheduler::GetInstance().Schedule(&m_defaultDrive);
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic() {
    double deadzone = 0.1;

    double driveLeft = ControlBinding::getInstance()->getControlStatus("driveLeft", deadzone);
    double driveRight = ControlBinding::getInstance()->getControlStatus("driveRight", deadzone);
    bool shift = ControlBinding::getInstance()->getControlStatus("shift");
    double shoot = ControlBinding::getInstance()->getControlStatus("shoot", deadzone);
    bool intake = ControlBinding::getInstance()->getControlStatus("intake");
    bool outtake = ControlBinding::getInstance()->getControlStatus("outtake");
    bool tiltIntake = ControlBinding::getInstance()->getControlStatus("tiltIntake");

    if (std::abs(driveLeft) > deadzone) {
        std::cout << "Drive Left: " << driveLeft << std::endl;
    }
    if (std::abs(driveRight) > deadzone) {
        std::cout << "Drive Right: " << driveRight << std::endl;
    }
    if (shift) {
        std::cout << "Shift" << std::endl;
    }
    if (std::abs(shoot) > deadzone) {
        std::cout << "Shoot: " << shoot << std::endl;
    }
    if (intake) {
        std::cout << "Intake" << std::endl;
    }
    if (outtake) {
        std::cout << "Outtake" << std::endl;
    }
    if (tiltIntake) {
        std::cout << "Tilt Intake" << std::endl;
    }
}

void Robot::TestInit() {
    TankSubsystem::getInstance()->setSpeed(0.0, 0.0);
}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
