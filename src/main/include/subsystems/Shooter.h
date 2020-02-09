#pragma once

#include <frc/DigitalInput.h>
#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>

#include "Constants.h"

class Shooter : public frc2::SubsystemBase {
    public:
        static Shooter* getInstance() {
            static Shooter instance;
            return &instance;
        }

        Shooter(Shooter const&) = delete;
        void operator = (Shooter const&) = delete;
        void initialize();
        void setFlywheelSpeed(const double& speed);
        void setShooterSpeed(const double& speed);
        void setLoaderSpeed(const double& speed);
        void setIntakeSpeed(const double& speed);
        void intakePowerCell();
        void activateIntakeTilt();
        void deactivateIntakeTilt();
        void execute();
        void stop();
    
    private:
        Shooter();
        TalonSRX m_flywheelLeft = {TALON_FLYWHEEL_LEFT};
        TalonSRX m_flywheelRight = {TALON_FLYWHEEL_RIGHT};
        TalonSRX m_shooterTop = {TALON_SHOOTER_TOP};
        TalonSRX m_shooterBottom = {TALON_SHOOTER_BOTTOM};
        TalonSRX m_loaderLeft = {TALON_LOADER_LEFT};
        TalonSRX m_loaderRight = {TALON_LOADER_RIGHT};
        TalonSRX m_intake = {TALON_INTAKE};
        frc::DigitalInput m_ballSensor{INPUT_LOADER_SENSOR};
};