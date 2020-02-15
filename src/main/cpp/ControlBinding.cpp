#include "ControlBinding.h"
#include "ControlModeDoesNotExistException.h"

ControlBinding::ControlBinding() {}

void ControlBinding::initialize() {
    // Driver controls
    m_controlData["driveLeft"] = {JoystickType::DRIVER, ControlType::AXIS, 1};
    m_controlData["driveRight"] = {JoystickType::DRIVER, ControlType::AXIS, 3};
    m_controlData["shiftHigh"] = {JoystickType::DRIVER, ControlType::BUTTON, 6};
    m_controlData["shiftLow"] = {JoystickType::DRIVER, ControlType::BUTTON, 5};
    m_controlData["switchCamera"] = {JoystickType::DRIVER, ControlType::BUTTON, 3};
    m_controlData["visionAim"] = {JoystickType::DRIVER, ControlType::BUTTON, 1};
    // Operator controls
    m_controlData["shoot"] = {JoystickType::OPERATOR, ControlType::AXIS, 3};
    m_controlData["intake"] = {JoystickType::OPERATOR, ControlType::BUTTON, 8};
    m_controlData["outtake"] = {JoystickType::OPERATOR, ControlType::BUTTON, 7};
    m_controlData["tiltIntakeUp"] = {JoystickType::OPERATOR, ControlType::BUTTON, 5};
    m_controlData["tiltIntakeDown"] = {JoystickType::OPERATOR, ControlType::BUTTON, 6};
}

double ControlBinding::getControlStatus(std::string control, double deadzone /* = 0 */) {
    auto it = m_controlData.find(control);

    // Determine if control mode is active
    try {
        if (it->second.driver == JoystickType::DRIVER && it->second.control == ControlType::AXIS) {
            double rawAxis = m_driverJoystick.GetRawAxis(it->second.id);
            return std::abs(rawAxis) > deadzone ? rawAxis : 0;
        } else if (it->second.driver == JoystickType::DRIVER && it->second.control == ControlType::BUTTON) {
            return m_driverJoystick.GetRawButton(it->second.id);
        } else if (it->second.driver == JoystickType::OPERATOR && it->second.control == ControlType::AXIS) {
            double rawAxis = m_operatorJoystick.GetRawAxis(it->second.id);
            return std::abs(rawAxis) > deadzone ? rawAxis : 0;
        } else if (it->second.driver == JoystickType::OPERATOR && it->second.control == ControlType::BUTTON) {
            return m_operatorJoystick.GetRawButton(it->second.id);
        }
    } catch (ControlModeDoesNotExistException e) {
        std::cout << e.printException() << std::endl;
    }

    return 0;
}