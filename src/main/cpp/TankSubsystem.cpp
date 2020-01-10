#include "TankSubsystem.h"
// #include "PCM.h"

TankSubsystem::TankSubsystem() : frc::Subsystem("TankSubsystem") {}

void TankSubsystem::init(){
    m_frontLeft.ConfigSelectedFeedbackSensor(CTRE_MagEncoder_Relative, 0, TIMEOUT);
    m_frontRight.ConfigSelectedFeedbackSensor(CTRE_MagEncoder_Relative, 0, TIMEOUT);
    
    m_backLeft.Follow(m_frontLeft);
    m_backRight.Follow(m_frontRight);

    m_frontLeft.SetInverted(false);
    m_backLeft.SetInverted(false);
    m_frontRight.SetInverted(true);
    m_backRight.SetInverted(true);

    m_frontLeft.ConfigNominalOutputForward(0, TIMEOUT);
	m_frontLeft.ConfigNominalOutputReverse(0, TIMEOUT);
	m_frontLeft.ConfigPeakOutputForward(1.0, TIMEOUT);
	m_frontLeft.ConfigPeakOutputReverse(-1.0, TIMEOUT);
	m_frontRight.ConfigNominalOutputForward(0, TIMEOUT);
	m_frontRight.ConfigNominalOutputReverse(0, TIMEOUT);
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