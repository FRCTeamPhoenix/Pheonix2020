#pragma once

#include <unordered_map>

#include <frc/Joystick.h>

#include "Constants.h"

enum class JoystickType {
    DRIVER, OPERATOR
};

enum class ControlType {
    AXIS, BUTTON
};

struct ControlData {
    JoystickType driver;
    ControlType control;
    int id;
};

class ControlBinding {
    public:
        static ControlBinding* getInstance() {
            static ControlBinding instance;
            return &instance;
        }

        ControlBinding(ControlBinding const&) = delete;
        void operator = (ControlBinding const&) = delete;
        ControlBinding();
        void initialize();
        bool getControlStatus(std::string control, double deadzone = 0);

    private:
        frc::Joystick m_driverJoystick{DRIVER_CONTROL};
        frc::Joystick m_operatorJoystick{OPERATOR_CONTROL};
        std::unordered_map<std::string, ControlData> m_controlData;
};