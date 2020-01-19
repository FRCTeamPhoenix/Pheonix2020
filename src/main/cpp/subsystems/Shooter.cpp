#include "subsystems/Shooter.h"

#include <frc/smartdashboard/SmartDashboard.h>

#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

Shooter::Shooter() {}

void Shooter:initialize() {
    // Configure encoders on motors (remove if encoder is absent)
    m_shooterTop.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, TIMEOUT);
    m_shooterBottom.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, TIMEOUT);
    m_loaderLeft.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, TIMEOUT);
    m_loaderRight.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, TIMEOUT);
    m_grabber.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, TIMEOUT);
    
    // Make sure bottom and top shooter belts go same direction
    m_shooterTop.SetInverted(true);
    m_shooterBottom.SetInverted(true);

    // Make sure left and right loader belts go same direction
    m_loaderLeft.SetInverted(true);
    m_loaderRight.SetInverted(true);

    // 
    m_shooterTop.ConfigNominalOutputForward(0, TIMEOUT);
    m_shooterTop.ConfigNominalOutputReverse(0, TIMEOUT);
    m_shooterBottom.ConfigNominalOutputForward(0, TIMEOUT);
    m_shooterBottom.ConfigNominalOutputReverse(0, TIMEOUT);
    m_loaderLeft.ConfigNominalOutputForward(0, TIMEOUT);
    m_loaderLeft.ConfigNominalOutputReverse(0, TIMEOUT);
    m_loaderRight.ConfigNominalOutputForward(0, TIMEOUT);
    m_loaderLeft.ConfigNominalOutputReverse(0, TIMEOUT);
    m_grabber.ConfigNominalOutputForward(0, TIMEOUT);
    m_grabber.ConfigNominalOutputReverse(0, TIMEOUT);

    // Configure power limits imposed on motors (change if needed)
    m_shooterTop.ConfigPeakOutputForward(1.0, TIMEOUT);
    m_shooterTop.ConfigPeakOutputReverse(-1.0, TIMEOUT);
    m_shooterBottom.ConfigPeakOutputForward(1.0, TIMEOUT);
    m_shooterBottom.ConfigPeakOutputReverse(-1.0, TIMEOUT);
    m_loaderLeft.ConfigPeakOutputForward(1.0, TIMEOUT);
    m_loaderLeft.ConfigPeakOutputReverse(-1.0, TIMEOUT);
    m_loaderRight.ConfigPeakOutputForward(1.0, TIMEOUT);
    m_loaderRight.ConfigPeakOutputReverse(-1.0, TIMEOUT);
}

void Shooter::setShooterSpeed(const double& top, const double& bottom) {
    m_shooterTop.Set(ControlMode::Velocity, top);
    m_shooterBottom.Set(ControlMode::Velocity, bottom);
}

void Shooter::setLoaderSpeed(const double& left, const double& right) {
    m_loaderLeft.Set(ControlMode::MotionMagic, left);
    m_loaderRight.Set(ControlMode::MotionMagic, right);
}

void Shooter::setGrabberSpeed(const double& front) {
    m_grabber.Set(ControlMode::PercentOutput, front);
}