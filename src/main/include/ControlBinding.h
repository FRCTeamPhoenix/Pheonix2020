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
        double getControlStatus(std::string control, double deadzone = 0);

    private:
        frc::Joystick m_driverJoystick{DRIVER_JOYSTICK};
        frc::Joystick m_operatorJoystick{OPERATOR_JOYSTICK};
        std::unordered_map<std::string, ControlData> m_controlData;
};