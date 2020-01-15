#pragma once

// Specifically using ControlMode, FeedbackDevice, and WPI_TalonSRX
#include <ctre/Phoenix.h>

#include <frc2/command/Subsystem.h>
#include <frc/Timer.h>

class Shooter {
    public:
        WPI_TalonSRX shooter;
        const int INTAKE = 0;
        const int OUTTAKE = 1;
        Shooter();
        void initialize();
        void end();
        void intake();
        void outtake();
        void outputToSmartDashboard();
    
    private:
        frc::Timer timer = new Timer();
}