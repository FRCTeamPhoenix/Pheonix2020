#include "commands/AimAdjust.h"

#include "Limelight.h"
#include "Constants.h"
#include "subsystems/TankSubsystem.h"
#include <iostream>
AimAdjust::AimAdjust(bool autoVersion) : m_autoVersion(autoVersion) {
    AddRequirements({TankSubsystem::getInstance()});
}

void AimAdjust::Initialize() {
    std::cout<<"Aim adjust started"<<std::endl;
}

void AimAdjust::Execute() {
    //adjust if the target is in view
    
    if(Limelight::seesTarget()){
        std::cout<<"Target found."<<std::endl;
        float err = Limelight::getTx();
        float targetCurrentDist = (TARGET_HEIGHT_IN - CAMERA_HEIGHT_IN) / tan((Limelight::getTy() + CAMERA_ANGLE) * PI / 180.0f);
        float distErr = targetCurrentDist - TARGET_DIST_IN;

        float speed = AIM_P * err + (err > AIM_THRESH ? AIM_FF : 0.0) + (err < -AIM_THRESH ? -AIM_FF : 0.0);
        float distSpeed = 0.0f;

        distSpeed = AIM_DIST_P * distErr;
        std::cout<<"distSpeed + speed: "<< distSpeed <<std::endl;
        std::cout<<"distSpeed - speed: "<< distSpeed <<std::endl;
        std::cout<<"About to set Speed." <<std::endl;
        TankSubsystem::getInstance()->setSpeed(distSpeed + speed, distSpeed - speed);
        std::cout<<"Speed set." <<std::endl;
    }
    else{
        std::cout<<"No target."<<std::endl;
    }
}

void AimAdjust::End(bool interrupted) {
    std::cout<<interrupted<<std::endl;
    TankSubsystem::getInstance()->setSpeed(0.0, 0.0);

    std::cout<<"Aim adjust over"<<std::endl;
}

bool AimAdjust::IsFinished() {
    std::cout<< "m_autoversion: " << m_autoVersion <<std::endl;
    if(m_autoVersion){
        float err = Limelight::getTx();
        float targetCurrentDist = (TARGET_HEIGHT_IN - CAMERA_HEIGHT_IN) / tan((Limelight::getTy() + CAMERA_ANGLE) * PI / 180.0f);
        float distErr = targetCurrentDist - TARGET_DIST_IN;

        std::cout<< (abs(err) < AIM_THRESH && abs(distErr) < DIST_TRESH) <<std::endl;
        
        return (abs(err) < AIM_THRESH && abs(distErr) < DIST_TRESH);
    }else{
        return !m_driverJoystick.GetRawButton(1);
    }
}