#pragma once

#include <string>
#include <unordered_map>

#include <frc/Joystick.h>
#include <frc2/command/button/JoystickButton.h>

#include "Constants.h"

enum class ControlType {
    AXIS, BUTTON
};

struct ControlData {
    ControlType type;
    int id;
};

class ControlBinding {
    public:
        ControlBinding();
        void initialize();
        bool getControlValue(std::string control);

    private:
        frc::Joystick m_driverJoystick{DRIVER_CONTROL};
        frc::Joystick m_operatorJoystick{OPERATOR_CONTROL};
        std::unordered_map<std::string, ControlData> m_controlData;
};