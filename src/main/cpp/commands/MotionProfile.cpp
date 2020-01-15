#include "commands/MotionProfile.h"

#include "subsystems/TankSubsystem.h"

MotionProfile::MotionProfile(){
    AddRequirements(TankSubsystem::getInstance());
}

void MotionProfile::Initialize(){
    m_frontLeft = TankSubsystem::getInstance()->getFrontLeft();

    ctre::phoenix::motion::BufferedTrajectoryPointStream stream;

    for(int i = 0; i < kMotionProfileSz; i++){
        ctre::phoenix::motion::TrajectoryPoint point;

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

        stream.Write(point);
    }

    m_frontLeft->StartMotionProfile(stream, kMotionProfileSz, ControlMode::MotionProfile);
}

bool MotionProfile::IsFinished(){
    return m_frontLeft->IsMotionProfileFinished();
}