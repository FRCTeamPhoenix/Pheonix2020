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

    Shooter::getInstance()->setLoaderSpeed(recoilSpeed * 0.15);
    Shooter::getInstance()->setShooterSpeed(recoilSpeed * 0.5);
    Shooter::getInstance()->setFlywheelSpeed(shoot * 0.5);
    Shooter::getInstance()->tiltIntakeUp(tiltIntakeUp);
    Shooter::getInstance()->tiltIntakeDown(tiltIntakeDown);

    if (intake) {
        std::cout<<"Push"<<std::endl;
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