#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/Joystick.h>

#include "Constants.h"
#include "subsystems/Shooter.h"

class ShootPowerCell : public frc2::CommandHelper<frc2::CommandBase, ShootPowerCell> {
    public:
        ShootPowerCell();
        void Initialize() override;
        void Execute() override;
        void End(bool interrupted) override;
        bool IsFinished() override;

    private:
        frc::Joystick m_operatorJoystick{OPERATOR_JOYSTICK};
};