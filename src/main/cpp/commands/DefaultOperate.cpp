#include "commands/DefaultOperate.h"
#include "ControlBinding.h"
#include "Constants.h"

DefaultOperate::DefaultOperate() {
    AddRequirements({Shooter::getInstance()});
}

void DefaultOperate::Initialize() {
    
}

void DefaultOperate::Execute() {
    double shoot = std::abs(ControlBinding::getInstance()->getControlStatus("shoot", DEADZONE));
    double recoilSpeed = shoot > DEADZONE ? 0.2 : 0;
    bool intake = ControlBinding::getInstance()->getControlStatus("intake") > 0.1;
    bool outtake = ControlBinding::getInstance()->getControlStatus("outtake") > 0.1;
    bool tiltIntake = ControlBinding::getInstance()->getControlStatus("tiltIntake") > 0.1;

    Shooter::getInstance()->setLoaderSpeed(recoilSpeed);
    Shooter::getInstance()->setShooterSpeed(recoilSpeed);
    Shooter::getInstance()->setFlywheelSpeed(shoot);
    Shooter::getInstance()->enableIntakeTilt(tiltIntake);

    if (intake) {
        Shooter::getInstance()->setIntakeSpeed(0.5);
    } else if (outtake) {
        Shooter::getInstance()->setIntakeSpeed(-0.5);
    } else {
        Shooter::getInstance()->setIntakeSpeed(0);
    }
}

void DefaultOperate::End(bool interrupted) {
    Shooter::getInstance()->stop();
}

bool DefaultOperate::IsFinished() {
    return false;
}
