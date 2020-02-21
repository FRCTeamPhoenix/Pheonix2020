#include "ControlBinding.h"
#include "ControlModeDoesNotExistException.h"

#include <frc/smartdashboard/SmartDashboard.h>

ControlBinding::ControlBinding() {}

void ControlBinding::initialize() {
    // Driver controls
    m_controlData["driveLeft"] = {JoystickType::DRIVER, ControlType::AXIS, 1};          // Left Axis
    m_controlData["driveRight"] = {JoystickType::DRIVER, ControlType::AXIS, 3};         // Right Axis
    m_controlData["shiftHigh"] = {JoystickType::DRIVER, ControlType::BUTTON, 8};        // Right Trigger
    m_controlData["shiftLow"] = {JoystickType::DRIVER, ControlType::BUTTON, 7};         // Left Trigger
    m_controlData["switchCamera"] = {JoystickType::DRIVER, ControlType::BUTTON, 3};     // Button 'B'
    m_controlData["visionAim"] = {JoystickType::DRIVER, ControlType::BUTTON, 1};        // Button 'X'
    // Operator controls
    m_controlData["moveloader"] = {JoystickType::OPERATOR, ControlType::AXIS, 1};       // Left Axis
    m_controlData["shoot"] = {JoystickType::OPERATOR, ControlType::AXIS, 3};            // Right Axis
    m_controlData["intake"] = {JoystickType::OPERATOR, ControlType::BUTTON, 8};         // Right Trigger
    m_controlData["outtake"] = {JoystickType::OPERATOR, ControlType::BUTTON, 7};        // Left Trigger
    m_controlData["tiltIntakeUp"] = {JoystickType::OPERATOR, ControlType::BUTTON, 5};   // Left Bumper
    m_controlData["tiltIntakeDown"] = {JoystickType::OPERATOR, ControlType::BUTTON, 6}; // Right Bumper

    displayControlBindings();
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
        std::cout << e.what() << std::endl;
    }

    return false;
}

void ControlBinding::displayControlBindings() {
    for(auto it = m_controlData.begin(); it != m_controlData.end(); it++){
        if (it->second.driver == JoystickType::DRIVER) {
            // Display driver control bindings
            m_driverControls->GetEntry(it->first).SetDouble(it->second.id);
        } else {
            // Display operator control bindings
            m_operatorControls->GetEntry(it->first).SetDouble(it->second.id);
        }
    }
}

void ControlBinding::updateControlBindings() {
    try {
        if (frc::SmartDashboard::GetBoolean("Save Controls")) {
            std::string control = frc::SmartDashboard::GetString("Control Mode");
            int newID = std::stoi(frc::SmartDashboard::GetString("ID"));
            auto it = m_controlData.find(control);
            it->second.id = newID;
        }
    } catch (std::exception& e) {
        std::cout << "Exception Occurred: " << e.what() << std::endl;
    }
}