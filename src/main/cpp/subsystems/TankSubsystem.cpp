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

    //change output to match + (input = output ?)
    m_frontLeft.SetSensorPhase(false);

    //invert left side motion (is it going the right way ?)
    m_frontLeft.SetInverted(true);
    m_backLeft.SetInverted(true);

    //change output to match +
    m_frontRight.SetSensorPhase(false);

    //invert the right side motion
    m_frontRight.SetInverted(false);
    m_backRight.SetInverted(false);

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
    
    m_frontLeft.Config_kP(0, 1.0);
    //(75% X 1023) / (speed at 75%)
    //left = 1092
    m_frontLeft.Config_kF(0, (.75 * 1023.0) / 1092.0);
    m_frontRight.Config_kP(0, 1.0);
    //right = 957
    m_frontRight.Config_kF(0, (.75 * 1023.0) / 957.0);
}

void TankSubsystem::setSpeed(const double& left, const double& right){
    m_frontLeft.Set(ControlMode::PercentOutput, left);
    m_frontRight.Set(ControlMode::PercentOutput, right);
}
void TankSubsystem::setHighGear() {
    PCMHandler::getInstance()->setHighGear();
}

void TankSubsystem::setLowGear(){
    PCMHandler::getInstance()->setLowGear();
}

void TankSubsystem::zeroEncoders(){
    m_frontLeft.GetSensorCollection().SetQuadraturePosition(0);
    m_frontRight.GetSensorCollection().SetQuadraturePosition(0);
    
}

void TankSubsystem::updateGyro(){
    
    //update the values
    frc::SmartDashboard::PutNumber("Gyro X", to180Scale((int)m_imu.GetAngleX()));
    frc::SmartDashboard::PutNumber("Gyro Y", to180Scale((int)m_imu.GetAngleY()));
    frc::SmartDashboard::PutNumber("Gyro Z", to180Scale((int)m_imu.GetAngleZ()));

    frc::SmartDashboard::PutNumber("Accel X", m_imu.GetAccelX());
    frc::SmartDashboard::PutNumber("Accel Y", m_imu.GetAccelY());
    frc::SmartDashboard::PutNumber("Accel Z", m_imu.GetAccelZ());

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