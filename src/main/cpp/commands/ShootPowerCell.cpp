#include "commands/ShootPowerCell.h"
#include "ControlBinding.h"
#include "Constants.h"

ShootPowerCell::ShootPowerCell() {
    AddRequirements({Shooter::getInstance()});
}

void ShootPowerCell::Initialize() {}

void ShootPowerCell::Execute() {
    double shoot = ControlBinding::getInstance()->getControlStatus("shoot", DEADZONE);
    std::cout << "Shoot: " << shoot << std::endl;
    Shooter::getInstance()->setShooterSpeed(-shoot);
    Shooter::getInstance()->setFlywheelSpeed(-shoot);
}

void ShootPowerCell::End(bool interrupted) {
    Shooter::getInstance()->setShooterSpeed(0);
    Shooter::getInstance()->setFlywheelSpeed(0);
}

bool ShootPowerCell::IsFinished() {
    return true;
}