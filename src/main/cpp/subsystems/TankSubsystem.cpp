#include "subsystems/TankSubsystem.h"
#include "PCMHandler.h"

#include <frc/smartdashboard/SmartDashboard.h>

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

void TankSubsystem::updateGyro(){
    
    //update the values
    frc::SmartDashboard::PutNumber("Gyro X", to180Scale((int)m_imu.GetAngleX()));
    frc::SmartDashboard::PutNumber("Gyro Y", to180Scale((int)m_imu.GetAngleY()));
    frc::SmartDashboard::PutNumber("Gyro Z", to180Scale((int)m_imu.GetAngleZ()));

    //calibrate gyro if button pressed
    if(frc::SmartDashboard::GetBoolean("GyroCalibrate",false)){
        m_imu.Calibrate();
    }

    if(frc::SmartDashboard::GetBoolean("GyroReset",false)){
        m_imu.Reset();
    }

    //reset the values
    frc::SmartDashboard::PutBoolean("GyroCalibrate", false);
    frc::SmartDashboard::PutBoolean("GyroReset", false);
}

int TankSubsystem::to180Scale(int original){
    return original > 0 ? (original + 180) % 360 - 180 : 180 - (abs(original) + 180) % 360; 
}