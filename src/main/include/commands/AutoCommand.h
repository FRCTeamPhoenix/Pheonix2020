#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/RamseteCommand.h>

class AutoCommand : public frc2::CommandHelper<frc2::SequentialCommandGroup, AutoCommand>
{
    public:
        AutoCommand();

    private:
        frc2::RamseteCommand getTrajectoryCommand();
};