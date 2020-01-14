#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include <frc/drive/DifferentialDrive.h>

#include "Constants.h"
#include "adi/ADIS16448_IMU.h"

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
        void setHighGear();
        void setLowGear();

        //used to check the dashboard for any calibration related things to gyro
        void updateGyro();

    private:
        TankSubsystem();

        int to180Scale(int original);

        frc::ADIS16448_IMU m_imu{};

        const int TIMEOUT = 10;

        WPI_TalonSRX m_frontLeft = {TALON_FRONT_LEFT};
        WPI_TalonSRX m_frontRight = {TALON_FRONT_RIGHT};
        WPI_TalonSRX m_backLeft = {TALON_BACK_LEFT};
        WPI_TalonSRX m_backRight = {TALON_BACK_RIGHT};

        frc::DifferentialDrive m_drive = frc::DifferentialDrive(m_frontLeft, m_frontRight);
};