#include "commands/Turn.h"
#include "subsystems/TankSubsystem.h"
#include "Constants.h"

#include <iostream>

Turn::Turn(const double& heading) : m_heading(heading){
    AddRequirements(TankSubsystem::getInstance());
}

void Turn::Initialize(){
    std::cout<<"Turn start"<<std::endl;
    TankSubsystem::getInstance()->setSpeed(0.0, 0.0);
    TankSubsystem::getInstance()->zeroGyro();
}

void Turn::Execute(){
    double err = m_heading- TankSubsystem::getInstance()->getFrontRight()->GetSelectedSensorPosition(1) / TICKS_PER_IMU_ROTATION * 360.0f;

    float speed =  (err > TURN_THRESH ? TURN_FF : TURN_P * err) + (err < -TURN_THRESH ? -TURN_FF : TURN_P * err);
    TankSubsystem::getInstance()->setSpeed(-speed, speed);
}

void Turn::End(bool interrupted){
    std::cout<<"Turn end"<<std::endl;
    TankSubsystem::getInstance()->setSpeed(0.0, 0.0);
}

bool Turn::IsFinished(){
    double err = abs(m_heading- TankSubsystem::getInstance()->getFrontRight()->GetSelectedSensorPosition(1) / TICKS_PER_IMU_ROTATION * 360.0f);
    return  err < TURN_END_TRESH;
}