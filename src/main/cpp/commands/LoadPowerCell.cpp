#include "commands/LoadPowerCell.h"

LoadPowerCell::LoadPowerCell() {
    AddRequirements({Shooter::getInstance()});
}

void LoadPowerCell::Initialize() {
    Shooter::getInstance()->loadPowerCell();
}

void LoadPowerCell::End(bool interrupted) {
    Shooter::getInstance()->setLoaderSpeed(0);
}

bool LoadPowerCell::IsFinished() {
    return true;
}