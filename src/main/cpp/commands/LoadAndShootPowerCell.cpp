#include "commands/LoadAndShootPowerCell.h"

LoadAndShootPowerCell::LoadAndShootPowerCell() {
    AddCommands(LoadPowerCell(), ShootPowerCell());
}