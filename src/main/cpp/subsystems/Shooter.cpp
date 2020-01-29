#include "subsystems/Shooter.h"

#include <frc/smartdashboard/SmartDashboard.h>

#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

Shooter::Shooter() {}

void Shooter::initialize() {
    // Configure encoders on motors (remove if encoder is absent)
    m_shooterTop.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0);
    m_shooterBottom.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0);
    m_loaderLeft.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0);
    m_loaderRight.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0);
    m_intake.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0);
    
    // Make sure bottom and top shooter belts go same direction
    m_shooterTop.SetInverted(true);
    m_shooterBottom.SetInverted(true);

    // Make sure left and right loader belts go same direction
    m_loaderLeft.SetInverted(true);
    m_loaderRight.SetInverted(true);

    // 
    m_shooterTop.ConfigNominalOutputForward(0);
    m_shooterTop.ConfigNominalOutputReverse(0);
    m_shooterBottom.ConfigNominalOutputForward(0);
    m_shooterBottom.ConfigNominalOutputReverse(0);
    m_loaderLeft.ConfigNominalOutputForward(0);
    m_loaderLeft.ConfigNominalOutputReverse(0);
    m_loaderRight.ConfigNominalOutputForward(0);
    m_loaderRight.ConfigNominalOutputReverse(0);
    m_intake.ConfigNominalOutputForward(0);
    m_intake.ConfigNominalOutputReverse(0);

    // Configure power limits on motors (change if needed)
    m_shooterTop.ConfigPeakOutputForward(1.0);
    m_shooterTop.ConfigPeakOutputReverse(-1.0);
    m_shooterBottom.ConfigPeakOutputForward(1.0);
    m_shooterBottom.ConfigPeakOutputReverse(-1.0);
    m_loaderLeft.ConfigPeakOutputForward(1.0);
    m_loaderLeft.ConfigPeakOutputReverse(-1.0);
    m_loaderRight.ConfigPeakOutputForward(1.0);
    m_loaderRight.ConfigPeakOutputReverse(-1.0);
    m_intake.ConfigPeakOutputForward(1.0);
    m_intake.ConfigPeakOutputReverse(-1.0);
    
    m_shooterTop.Follow(m_shooterBottom);
    m_loaderLeft.Follow(m_loaderRight);
}

void Shooter::setShooterSpeed(const double& speed) {
    m_shooterTop.Set(ControlMode::Velocity, speed);
    m_shooterBottom.Set(ControlMode::Velocity, speed);
}

void Shooter::setLoaderSpeed(const double& speed) {
    m_loaderLeft.Set(ControlMode::MotionMagic, speed);
    m_loaderRight.Set(ControlMode::MotionMagic, speed);
}

void Shooter::setIntakeSpeed(const double& speed) {
    m_intake.Set(ControlMode::PercentOutput, speed);
}

void Shooter::stop() {
    setShooterSpeed(0);
    setLoaderSpeed(0);
    setIntakeSpeed(0);
}