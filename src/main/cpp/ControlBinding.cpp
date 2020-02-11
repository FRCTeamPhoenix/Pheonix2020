#include "ControlBinding.h"
#include "ControlModeDoesNotExistException.h"

ControlBinding::ControlBinding() {}

void ControlBinding::initialize() {
    // Driver controls
    m_controlData["driveLeft"] = {JoystickType::DRIVER, ControlType::AXIS, 1};
    m_controlData["driveRight"] = {JoystickType::DRIVER, ControlType::AXIS, 3};
    m_controlData["shift"] = {JoystickType::DRIVER, ControlType::BUTTON, 6};
    // Operator controls
    m_controlData["shoot"] = {JoystickType::OPERATOR, ControlType::AXIS, 3};
    m_controlData["intake"] = {JoystickType::OPERATOR, ControlType::BUTTON, 8};
    m_controlData["outtake"] = {JoystickType::OPERATOR, ControlType::BUTTON, 7};
    m_controlData["tiltIntake"] = {JoystickType::OPERATOR, ControlType::BUTTON, 6};
}

bool ControlBinding::getControlStatus(std::string control, double deadzone /* = 0 */) {
    auto it = m_controlData.find(control);

    // Determine if control mode is active
    try {
        if (it->second.driver == JoystickType::DRIVER && it->second.control == ControlType::AXIS) {
            return abs(m_driverJoystick.GetRawAxis(it->second.id)) > deadzone;
        } else if (it->second.driver == JoystickType::DRIVER && it->second.control == ControlType::BUTTON) {
            return m_driverJoystick.GetRawButton(it->second.id);
        } else if (it->second.driver == JoystickType::OPERATOR && it->second.control == ControlType::AXIS) {
            return abs(m_operatorJoystick.GetRawAxis(it->second.id)) > deadzone;
        } else if (it->second.driver == JoystickType::OPERATOR && it->second.control == ControlType::BUTTON) {
            return m_operatorJoystick.GetRawButton(it->second.id);
        }
    } catch (ControlModeDoesNotExistException e) {
        std::cout << e.printException() << std::endl;
    }

    return false;
}