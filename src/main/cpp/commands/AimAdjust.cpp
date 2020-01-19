#include "commands/AimAdjust.h"

#include "Limelight.h"
#include "Constants.h"
#include "subsystems/TankSubsystem.h"
#include <iostream>
AimAdjust::AimAdjust(){
    AddRequirements({TankSubsystem::getInstance()});
}

void AimAdjust::Initialize() {
}

void AimAdjust::Execute() {
    //adjust if the target is in view
    if(Limelight::seesTarget()){
        float err = Limelight::getTx();
        float targetCurrentDist = (TARGET_HEIGHT_IN - CAMERA_HEIGHT_IN) / tan((Limelight::getTy() + CAMERA_ANGLE) * PI / 180.0f);
        float distErr = targetCurrentDist - TARGET_DIST_IN;

        float speed = AIM_P * err + (err > AIM_THRESH ? AIM_FF : 0.0) + (err < -AIM_THRESH ? -AIM_FF : 0.0);
        float distSpeed = 0.0f;

        distSpeed = AIM_DIST_P * distErr;

        TankSubsystem::getInstance()->setSpeed(distSpeed + speed, distSpeed -speed);
    }
}

void AimAdjust::End(bool interrupted) {
    TankSubsystem::getInstance()->setSpeed(0.0, 0.0);
}

bool AimAdjust::IsFinished() {
    return !m_driverJoystick.GetRawButton(1);
}