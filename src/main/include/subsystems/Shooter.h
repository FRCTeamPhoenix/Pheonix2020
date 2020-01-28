#pragma once

#include <ctre/Phoenix.h>

#include <frc2/command/Subsystem.h>
#include <frc2/command/SubsystemBase.h>

class Shooter : public frc2::SubsystemBase {
    public:
        static Shooter* getInstance() {
            static Shooter instance;
            return &instance;
        }

        Shooter(Shooter const&) = delete;
        void operator = (Shooter const&) = delete;
        void initialize();
        void setShooterSpeed(const double& speed);
        void setLoaderSpeed(const double& speed);
        void setGrabberSpeed(const double& speed);
        void grab();
        void reload();
        void shootLow();
        void shootHigh();
        void stop();
    
    private:
        Shooter();
        // const int TIMEOUT = 10;
        TalonSRX m_shooterTop;
        TalonSRX m_shooterBottom;
        TalonSRX m_loaderLeft;
        TalonSRX m_loaderRight;
        TalonSRX m_grabber;
}