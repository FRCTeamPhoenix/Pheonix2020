#include "commands/IntakePowerCell.h"

IntakePowerCell::IntakePowerCell() {
    AddRequirements({Shooter::getInstance()});
}

void IntakePowerCell::Initialize() {
    Shooter::getInstance()->intakePowerCell();
}

void IntakePowerCell::End(bool interrupted) {
    Shooter::getInstance()->setIntakeSpeed(0);
}

bool IntakePowerCell::IsFinished() {
    return true;
}