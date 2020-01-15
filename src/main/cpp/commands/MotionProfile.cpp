#include "commands/MotionProfile.h"

#include "subsystems/TankSubsystem.h"

MotionProfile::MotionProfile(){
    AddRequirements(TankSubsystem::getInstance());

    //allocate a new one to prevent copy operation
    m_stream = new ctre::phoenix::motion::BufferedTrajectoryPointStream();

}

void MotionProfile::Initialize(){
    m_frontLeft = TankSubsystem::getInstance()->getFrontLeft();
    m_frontLeft->ClearMotionProfileTrajectories();
    
    m_stream->Clear();

    ctre::phoenix::motion::TrajectoryPoint point;
    for(int i = 0; i < kMotionProfileSz; i++){
        double positionRot = kMotionProfile[i][0];
        double velocityRPM = kMotionProfile[i][1];
        int durationMilliseconds = (int) kMotionProfile[i][2];

        /* for each point, fill our structure and pass it to API */
        point.timeDur = durationMilliseconds;
        point.position = positionRot * 4096;           // Convert Revolutions to Units
        point.velocity = velocityRPM * 4096 / 600.0;   // Convert RPM to Units/100ms
        point.auxiliaryPos = 0;
        point.auxiliaryVel = 0;
        point.profileSlotSelect0 = 0; /* which set of gains would you like to use [0,3]? */
        point.profileSlotSelect1 = 0; /* auxiliary PID [0,1], leave zero */
        point.zeroPos = (i == 0); /* set this to true on the first point */
        point.isLastPoint = ((i + 1) == kMotionProfileSz); /* set this to true on the last point */
        point.arbFeedFwd = 0; /* you can add a constant offset to add to PID[0] output here */

        m_stream->Write(point);
    }

    std::cout<<"write finished"<<std::endl;
    m_frontLeft->StartMotionProfile(*m_stream, 10, ControlMode::MotionProfile);
    std::cout<<"motion profile started"<<std::endl;
}

void MotionProfile::End(bool interrupted)
{
    std::cout<<"motion profile end"<<std::endl;
}

bool MotionProfile::IsFinished(){
    bool isFinished = m_frontLeft->IsMotionProfileFinished();
    std::cout<< isFinished <<std::endl;
    return isFinished;
}