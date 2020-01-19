#include "commands/AimAdjust.h"

#include "Limelight.h"
#include "Constants.h"
#include "subsystems/TankSubsystem.h"
#include <iostream>
AimAdjust::AimAdjust(){
    AddRequirements({TankSubsystem::getInstance()});
}

void AimAdjust::Initialize() {
    std::cout<<"started aim"<<std::endl;
}

void AimAdjust::Execute() {
    //adjust if the target is in view
    if(Limelight::seesTarget()){
        float err = Limelight::getTx();

        float speed = AIM_P * err + (err > AIM_THRESH ? AIM_FF : 0.0) + (err < -AIM_THRESH ? -AIM_FF : 0.0);

        TankSubsystem::getInstance()->setSpeed(speed, -speed);
    }
}

void AimAdjust::End(bool interrupted) {
    TankSubsystem::getInstance()->setSpeed(0.0, 0.0);
}

bool AimAdjust::IsFinished() {
    return !m_driverJoystick.GetRawButton(1);
}