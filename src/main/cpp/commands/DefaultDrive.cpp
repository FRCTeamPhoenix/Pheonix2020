#include "commands/DefaultDrive.h"

DefaultDrive::DefaultDrive() {
    AddRequirements({TankSubsystem::getInstance()});
}

void DefaultDrive::Initialize() {

}

void DefaultDrive::Execute() {
    std::cout<<"Drive"<<std::endl;
    TankSubsystem::getInstance()->setSpeed(-m_driverJoystick.GetRawAxis(1), -m_driverJoystick.GetRawAxis(3));
}

void DefaultDrive::End(bool interrupted) {
    TankSubsystem::getInstance()->setSpeed(0.0, 0.0);
}

bool DefaultDrive::IsFinished() {
    return false;
}
