/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>
#include "subsystems/TankSubsystem.h"
#include "commands/AutoCommand.h"
#include "PCMHandler.h"

void Robot::RobotInit() {

    TankSubsystem::getInstance()->init();
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
    TankSubsystem::getInstance()->updateGyro();

    //get and print the pose stuff
    TankSubsystem::getInstance()->updateOdometry();
    auto pose = TankSubsystem::getInstance()->getPose();

    frc::SmartDashboard::PutNumber("gyroThing",pose.Rotation().Degrees().toLinearized<int>());
    frc::SmartDashboard::PutNumber("X",pose.Translation().X().toLinearized<double>());
    frc::SmartDashboard::PutNumber("Y",pose.Translation().Y().toLinearized<double>());
    
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
    //make sure the PCM is turned on
    PCMHandler::getInstance()->turnOn();

    //init the tank subsystem
    TankSubsystem::getInstance()->init();

    //set it to high gear
    TankSubsystem::getInstance()->setHighGear();
}

void Robot::AutonomousPeriodic() {
    TankSubsystem::getInstance()->updateOdometry();
}

void Robot::TeleopInit() {
    //reset to zero
    TankSubsystem::getInstance()->zeroEncoders();

    //make sure the PCM is turned on
    PCMHandler::getInstance()->turnOn();

    //init the tank subsystem
    TankSubsystem::getInstance()->init();
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic() {}

void Robot::TestInit() {
    //make sure the PCM is turned on
    PCMHandler::getInstance()->turnOn();

    //init the tank subsystem
    TankSubsystem::getInstance()->init();

    TankSubsystem::getInstance()->zeroEncoders();

    //set it to high gear
    TankSubsystem::getInstance()->setHighGear();

    frc2::CommandScheduler::GetInstance().Schedule(&m_autoCommand);
}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {
    frc2::CommandScheduler::GetInstance().Run();
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
