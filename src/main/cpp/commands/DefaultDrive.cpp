#include "commands/DefaultDrive.h"
#include "ControlBinding.h"
#include "Constants.h"

DefaultDrive::DefaultDrive() {
    AddRequirements({TankSubsystem::getInstance()});
}

void DefaultDrive::Initialize() {

}

void DefaultDrive::Execute() {
    double driveLeft = ControlBinding::getInstance()->getControlStatus("driveLeft", DEADZONE);
    double driveRight = ControlBinding::getInstance()->getControlStatus("driveRight", DEADZONE);
    TankSubsystem::getInstance()->setSpeed(-driveLeft, -driveRight);
}

void DefaultDrive::End(bool interrupted) {
    TankSubsystem::getInstance()->setSpeed(0.0, 0.0);
}

bool DefaultDrive::IsFinished() {
    return false;
}
