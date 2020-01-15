#include "commands/DefaultDrive.h"

DefaultDrive::DefaultDrive() {
    AddRequirements({TankSubsystem::getInstance()});
}

void DefaultDrive::initialize() {}

void DefaultDrive::execute() {
    TankSubsystem::getInstance()->setSpeed(m_driverJoystick.GetX(), m_driverJoystick.GetY());
}

void DefaultDrive::end() {
    TankSubsystem::getInstance()->setSpeed(0.0, 0.0);
}

bool DefaultDrive::isFinished() {
    return false;
}

void DefaultDrive::interrupt() {
    end();
}