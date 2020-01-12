#include "commands/AutoCommand.h"

#include <frc/trajectory/constraint/DifferentialDriveVoltageConstraint.h>
#include <frc/trajectory/Trajectory.h>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc/trajectory/TrajectoryConfig.h>

#include <frc2/command/InstantCommand.h>

#include "Constants.h"
#include "subsystems/TankSubsystem.h"

AutoCommand::AutoCommand(){
    frc2::InstantCommand e{[this]{std::cout<<"In position"<<std::endl;}};

    AddCommands(
        getTrajectoryCommand(),
        e
    );
}

frc2::RamseteCommand AutoCommand::getTrajectoryCommand(){
    //create a constraint on voltage to prevent over drawing
    frc::DifferentialDriveVoltageConstraint autoVoltageConstraint(
        frc::SimpleMotorFeedforward<units::meters>(kS, kV, kA), DRIVE_KINEMATICS, 10_V
    );

    //set up our trajectory config for speeds
    frc::TrajectoryConfig config(MAX_SPEED, MAX_ACCELERATION);
    //set the kinematics for maximum speed
    config.SetKinematics(DRIVE_KINEMATICS);
    //add the rules for voltage
    config.AddConstraint(autoVoltageConstraint);

    auto straightTrajectory = frc::TrajectoryGenerator::GenerateTrajectory(
        //start facing forward
        frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)),
        //don't want any waypoints for now
        {frc::Translation2d(1_m, 0_m)},
        frc::Pose2d(3_m, 0_m, frc::Rotation2d(0_deg)),
        config);

    PID left = TankSubsystem::getInstance()->getLeftPIDValue(PID_DISTANCE_SLOT);
    PID right = TankSubsystem::getInstance()->getRightPIDValue(PID_DISTANCE_SLOT);

    frc2::RamseteCommand ramseteCommand(
        straightTrajectory, [this]() { return TankSubsystem::getInstance()->getPose(); },
        frc::RamseteController(RAMSETE_B, RAMSETE_ZETA),
        frc::SimpleMotorFeedforward<units::meters>(kS, kV, kA),
        DRIVE_KINEMATICS,
        [this] {return TankSubsystem::getInstance()->getWheelSpeeds(); },
        frc2::PIDController(left.P, left.I, left.D),
        frc2::PIDController(right.P, right.I, right.D),
        [this](auto left, auto right){TankSubsystem::getInstance()->setVoltage(left,right); },
        {TankSubsystem::getInstance()}
    );

    return ramseteCommand;
}