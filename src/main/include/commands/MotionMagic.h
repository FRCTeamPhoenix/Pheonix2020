#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <ctre/Phoenix.h>

class MotionMagic : public frc2::CommandHelper<frc2::CommandBase, MotionMagic>{
public:
    MotionMagic(const double& distance, const double& heading, const double& maxErr, const double& maxErrHeading);

    void Initialize() override;

    void Execute() override;

    void End(bool interrupted) override;

    bool IsFinished() override;
private:
    double m_distance, m_heading, m_maxErr, m_maxErrHeading;

    TalonSRX* m_frontRight;
};