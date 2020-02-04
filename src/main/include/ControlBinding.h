#pragma once

#include <frc/Joystick.h>
#include <frc2/command/button/JoystickButton.h>

#include "Constants.h"

class ControlBinding {
    public:
        void initialize();
        void execute();
        void end();
        // Driver controls
        bool shiftGearButtonIsPressed();
        bool leftDriveAxisIsActive();
        bool rightDriveAxisIsActive();
        // Operator controls
        bool shooterButtonIsPressed();
        bool intakeButtonIsPressed();
        bool intakeTiltAxisIsActive();

    private:
        frc::Joystick m_driverJoystick{DRIVER_CONTROL};
        frc::Joystick m_operatorJoystick{OPERATOR_CONTROL};
}