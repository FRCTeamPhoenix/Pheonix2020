#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

class Turn : public frc2::CommandHelper<frc2::CommandBase, Turn>{
public:
    Turn(const double& heading);

    void Initialize() override;

    void Execute() override;

    void End(bool interrupted) override;

    bool IsFinished() override;
private:
    double m_heading;
};