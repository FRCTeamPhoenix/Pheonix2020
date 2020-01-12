#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>

#include "Constants.h"
#include "adi/ADIS16448_IMU.h"

struct PID{
    double P;
    double I;
    double D;
    double F;
};

class TankSubsystem : public frc2::SubsystemBase {
    public:
        //have a singleton based subsytem since you will only have 1 object
        static TankSubsystem* getInstance(){
            static TankSubsystem instance;
            
            return &instance;
        }

        //prevent copying
        TankSubsystem(TankSubsystem const&) = delete;
        void operator=(TankSubsystem const&)  = delete;

        void init();

        void setSpeed(const double& left, const double& right);
        void setVoltage(units::volt_t left, units::volt_t right);
        void setHighGear();
        void setLowGear();

        //update the odometry periodically
        void updateOdometry();

        //zero the encoders
        void zeroEncoders();

        //used to check the dashboard for any calibration related things to gyro
        void updateGyro();

        //return the current pose
        frc::Pose2d getPose() const {return m_odometry.GetPose();}

        //get wheel speeds
        frc::DifferentialDriveWheelSpeeds getWheelSpeeds();

        PID getLeftPIDValue(int index);
        PID getRightPIDValue(int index);
    private:
        TankSubsystem();

        int to180Scale(int original);

        frc::ADIS16448_IMU m_imu{};

        const int TIMEOUT = 10;

        WPI_TalonSRX m_masterLeft = {TALON_MASTER_LEFT};
        WPI_TalonSRX m_masterRight = {TALON_MASTER_RIGHT};
        WPI_TalonSRX m_slaveLeft = {TALON_SLAVE_LEFT};
        WPI_TalonSRX m_slaveRight = {TALON_SLAVE_RIGHT};

        //the odometry used for field positioning
        frc::DifferentialDriveOdometry m_odometry{frc::Rotation2d(0_deg)};

        frc::DifferentialDrive m_drive = frc::DifferentialDrive(m_masterLeft, m_masterRight);
};