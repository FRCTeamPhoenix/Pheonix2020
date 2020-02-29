#include "commands/DefaultOperate.h"
#include "ControlBinding.h"
#include "Constants.h"

DefaultOperate::DefaultOperate() {
    AddRequirements({Shooter::getInstance()});
}

void DefaultOperate::Initialize() {
    
}

void DefaultOperate::Execute() {
    double shoot = -ControlBinding::getInstance()->getControlStatus("shoot");
    double recoilSpeed = -ControlBinding::getInstance()->getControlStatus("moveloader");
    bool intake = ControlBinding::getInstance()->getControlStatus("intake") > 0.1;
    bool outtake = ControlBinding::getInstance()->getControlStatus("outtake") > 0.1;
    bool tiltIntakeUp = ControlBinding::getInstance()->getControlStatus("tiltIntakeUp") > 0.1;
    bool tiltIntakeDown = ControlBinding::getInstance()->getControlStatus("tiltIntakeDown") > 0.1;

    Shooter::getInstance()->setLoaderSpeed(recoilSpeed * LOADER_SPEED);
    Shooter::getInstance()->setShooterSpeed(recoilSpeed * SHOOTER_SPEED);
    Shooter::getInstance()->setFlywheelSpeed(shoot * FLYWHEEL_SPEED);
    Shooter::getInstance()->tiltIntakeUp(tiltIntakeUp);
    Shooter::getInstance()->tiltIntakeDown(tiltIntakeDown);

    if (intake) {
        Shooter::getInstance()->setIntakeSpeed(INTAKE_SPEED);
    } else if (outtake) {
        Shooter::getInstance()->setIntakeSpeed(-INTAKE_SPEED);
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
