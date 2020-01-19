#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/Joystick.h>

#include "subsystems/TankSubsystem.h"

class DefaultDrive : public frc2::CommandHelper<frc2::CommandBase, DefaultDrive> {
    public:
        DefaultDrive();
        void Initialize() override;

        void Execute() override;

        void End(bool interrupted) override;

        bool IsFinished() override;
    
    private:
        frc::Joystick m_driverJoystick{0};
};