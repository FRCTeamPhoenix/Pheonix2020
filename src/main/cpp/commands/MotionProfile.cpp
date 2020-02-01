#include "commands/MotionProfile.h"

#include "subsystems/TankSubsystem.h"

#include <iostream>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>

MotionProfile::MotionProfile(){
    AddRequirements(TankSubsystem::getInstance());
}

void MotionProfile::Initialize(){
    //allocate a new one to prevent copy operation
    m_rightStream = new ctre::phoenix::motion::BufferedTrajectoryPointStream();

    //delete any possible existing data
    int err = m_rightStream->Clear();

    //print out errors
    if(err != 0){
        std::cout<<"Clear failed: "<<err<<std::endl;
    }

    double turnAmount = 0.5 * 8192.0; //8192 units per rotation for a pigeon

    ctre::phoenix::motion::TrajectoryPoint point;
    for(int i = 0; i < kMotionProfileSz; i++){
        double positionRot = kMotionProfile[i][0];
        double velocityRPM = kMotionProfile[i][1];
        int durationMilliseconds = (int)kMotionProfile[i][2];

        /* for each point, fill our structure and pass it to API */
        point.timeDur = durationMilliseconds;
        point.position = positionRot * TICKS_PER_REV;           // Convert Revolutions to Units
        point.velocity = velocityRPM * TICKS_PER_REV / 600.0;   // Convert RPM to Units/100ms
        point.auxiliaryPos = turnAmount; //heading of the robot
        point.auxiliaryVel = 0;
        point.profileSlotSelect0 = PID_VELOCITY_SLOT; /* which set of gains would you like to use [0,3]? */
        point.profileSlotSelect1 = PID_HEADING_SLOT; /* auxiliary PID [0,1], leave zero */
        point.zeroPos = (i == 0); /* set this to true on the first point */
        point.isLastPoint = ((i + 1) == kMotionProfileSz); /* set this to true on the last point */
        point.arbFeedFwd = 0; /* you can add a constant offset to add to PID[0] output here */
        point.useAuxPID = true;

        err = m_rightStream->Write(point);
        if(err != 0){
            std::cout<<"Write failed: "<<err<<std::endl;
        }
    }

    m_frontRight = TankSubsystem::getInstance()->getFrontRight();

    std::cout<<"write finished"<<std::endl;
    
    //make it aux follow for pid loops
    TankSubsystem::getInstance()->getFrontLeft()->Follow(*m_frontRight, FollowerType_AuxOutput1);
    err = m_frontRight->StartMotionProfile(*m_rightStream, 10, ControlMode::MotionProfileArc);
    if(err != 0){
        std::cout<<"StartMotionProfile failed: "<<err<<std::endl;
    }
    std::cout<<"motion profile started"<<std::endl;
}

void MotionProfile::Execute(){
}

void MotionProfile::End(bool interrupted)
{
    TankSubsystem::getInstance()->setSpeed(0.0, 0.0);
    std::cout<<"motion profile end"<<std::endl;
}

bool MotionProfile::IsFinished(){
    bool isFinished = m_frontRight->IsMotionProfileFinished();
    return isFinished;
}