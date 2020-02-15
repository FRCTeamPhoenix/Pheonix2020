#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/ParallelCommandGroup.h>

#include "Constants.h"
#include "commands/LoadPowerCell.h"
#include "commands/ShootPowerCell.h"

class LoadAndShootPowerCell : public frc2::CommandHelper<frc2::ParallelCommandGroup, LoadAndShootPowerCell> {
    public:
        LoadAndShootPowerCell();
};