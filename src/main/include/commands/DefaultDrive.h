#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/Joystick.h>
#include "Robot.h"

#include "subsystems/TankSubsystem.h"

class DefaultDrive : public frc2::CommandHelper<frc2::CommandBase, DefaultDrive> {
    public:
        DefaultDrive();
        void initialize();
        void execute();
        void end();
        bool isFinished();
        void interrupt();
    
    private:
        frc::Joystick m_driverJoystick{0};
}