#include "subsystems/TankSubsystem.h"
#include "PCMHandler.h"

TankSubsystem::TankSubsystem() {
    
}

void TankSubsystem::init(){
    //switch what sensor we want to feedback
    m_frontLeft.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, TIMEOUT);
    m_frontRight.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, TIMEOUT);
    
    m_backLeft.Follow(m_frontLeft);
    m_backRight.Follow(m_frontRight);

    //keep the left sensors the way they are
    m_frontLeft.SetInverted(false);
    m_backLeft.SetInverted(false);

    //invert the right side sensors
    m_frontRight.SetInverted(true);
    m_backRight.SetInverted(true);

    //prevent the motors from bumping small percents to a minimum
    m_frontLeft.ConfigNominalOutputForward(0, TIMEOUT);
	m_frontLeft.ConfigNominalOutputReverse(0, TIMEOUT);
	m_frontRight.ConfigNominalOutputForward(0, TIMEOUT);
	m_frontRight.ConfigNominalOutputReverse(0, TIMEOUT);

    //allow us to use the full motor power without a cap
    m_frontLeft.ConfigPeakOutputForward(1.0, TIMEOUT);
	m_frontLeft.ConfigPeakOutputReverse(-1.0, TIMEOUT);
	m_frontRight.ConfigPeakOutputForward(1.0, TIMEOUT);
    m_frontRight.ConfigPeakOutputReverse(-1.0, TIMEOUT);
}

void TankSubsystem::setSpeed(const double& left, const double& right){
    m_drive.TankDrive(left, right);
}
void TankSubsystem::setHighGear() {
    PCMHandler::getInstance()->setHighGear();
}

void TankSubsystem::setLowGear(){
    PCMHandler::getInstance()->setLowGear();
}