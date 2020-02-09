#include "commands/ShootPowerCell.h"

ShootPowerCell::ShootPowerCell() {
    AddRequirements({Shooter::getInstance()});
}

void ShootPowerCell::Initialize() {}

void ShootPowerCell::Execute() {
    Shooter::getInstance()->setShooterSpeed(m_operatorJoystick.GetRawAxis(1));
    Shooter::getInstance()->setFlywheelSpeed(m_operatorJoystick.GetRawAxis(1));
}

void ShootPowerCell::End(bool interrupted) {
    Shooter::getInstance()->setShooterSpeed(0);
    Shooter::getInstance()->setFlywheelSpeed(0);
}

bool ShootPowerCell::IsFinished() {
    return true;
}