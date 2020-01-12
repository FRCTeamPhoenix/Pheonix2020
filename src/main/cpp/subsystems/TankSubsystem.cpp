#include "subsystems/TankSubsystem.h"
#include "PCMHandler.h"

#include <frc/smartdashboard/SmartDashboard.h>

TankSubsystem::TankSubsystem() {
    
}

void TankSubsystem::init(){
    //switch what sensor we want to feedback
    m_masterLeft.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, TIMEOUT);
    m_masterRight.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, TIMEOUT);
    m_masterLeft.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 1, TIMEOUT);
    m_masterRight.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 1, TIMEOUT);

    m_slaveLeft.Follow(m_masterLeft);
    m_slaveRight.Follow(m_masterRight);

    //keep the left sensors the way they are
    m_masterLeft.SetInverted(true);
    // m_slaveLeft.SetInverted(true);

    //invert the right side sensors
    m_masterRight.SetInverted(false);
    // m_slaveRight.SetInverted(false);

    //prevent the motors from bumping small percents to a minimum
    m_masterLeft.ConfigNominalOutputForward(0, TIMEOUT);
	m_masterLeft.ConfigNominalOutputReverse(0, TIMEOUT);
	m_masterRight.ConfigNominalOutputForward(0, TIMEOUT);
	m_masterRight.ConfigNominalOutputReverse(0, TIMEOUT);

    //allow us to use the full motor power without a cap
    m_masterLeft.ConfigPeakOutputForward(1.0, TIMEOUT);
	m_masterLeft.ConfigPeakOutputReverse(-1.0, TIMEOUT);
	m_masterRight.ConfigPeakOutputForward(1.0, TIMEOUT);
    m_masterRight.ConfigPeakOutputReverse(-1.0, TIMEOUT);
}

void TankSubsystem::setSpeed(const double& left, const double& right){
    m_drive.TankDrive(left, right);
}

void TankSubsystem::setVoltage(units::volt_t left, units::volt_t right){
    frc::SmartDashboard::PutNumber("left", left.toLinearized<double>());
    frc::SmartDashboard::PutNumber("right", right.toLinearized<double>());
    m_masterLeft.SetVoltage(left);
    m_masterRight.SetVoltage(right);
}

void TankSubsystem::setHighGear() {
    PCMHandler::getInstance()->setHighGear();
}

void TankSubsystem::setLowGear(){
    PCMHandler::getInstance()->setLowGear();
}

void TankSubsystem::updateOdometry(){
    m_odometry.Update(frc::Rotation2d(units::degree_t(0.0f)),
    units::meter_t(m_masterLeft.GetSelectedSensorPosition() * TICKS_TO_DISTANCE_FT),
     units::meter_t(m_masterRight.GetSelectedSensorPosition() * TICKS_TO_DISTANCE_FT));

    frc::SmartDashboard::PutNumber("left",m_masterLeft.GetSelectedSensorPosition());
    frc::SmartDashboard::PutNumber("right",m_masterRight.GetSelectedSensorPosition());
}

void TankSubsystem::zeroEncoders(){
    //set the positions of each of the sensors to zero
    m_masterLeft.GetSensorCollection().SetQuadraturePosition(0);
    m_masterRight.GetSensorCollection().SetQuadraturePosition(0);
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

frc::DifferentialDriveWheelSpeeds TankSubsystem::getWheelSpeeds(){
    return {units::meters_per_second_t(m_masterLeft.GetSelectedSensorVelocity() * TICKS_TO_DISTANCE_FT * 10),
          units::meters_per_second_t(m_masterRight.GetSelectedSensorVelocity() * TICKS_TO_DISTANCE_FT * 10)};
}

PID TankSubsystem::getLeftPIDValue(int index){
    PID pid;
    pid.P = m_masterLeft.ConfigGetParameter(ParamEnum::eProfileParamSlot_P, index);
    pid.I = m_masterLeft.ConfigGetParameter(ParamEnum::eProfileParamSlot_I, index);
    pid.D = m_masterLeft.ConfigGetParameter(ParamEnum::eProfileParamSlot_D, index);
    pid.F = m_masterLeft.ConfigGetParameter(ParamEnum::eProfileParamSlot_F, index);

    return pid;
}

PID TankSubsystem::getRightPIDValue(int index){
    PID pid;
    pid.P = m_masterRight.ConfigGetParameter(ParamEnum::eProfileParamSlot_P, index);
    pid.I = m_masterRight.ConfigGetParameter(ParamEnum::eProfileParamSlot_I, index);
    pid.D = m_masterRight.ConfigGetParameter(ParamEnum::eProfileParamSlot_D, index);
    pid.F = m_masterRight.ConfigGetParameter(ParamEnum::eProfileParamSlot_F, index);

    return pid;
}

int TankSubsystem::to180Scale(int original){
    return original > 0 ? (original + 180) % 360 - 180 : 180 - (abs(original) + 180) % 360; 
}