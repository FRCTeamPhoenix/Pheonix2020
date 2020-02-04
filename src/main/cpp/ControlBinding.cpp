#include "ControlBinding.h"

ControlBinding::ControlBinding() {}

void ControlBinding::initialize() {
    m_controlData["driveLeft"] = {ControlType::AXIS, 0};
    m_controlData["driveRight"] = {ControlType::AXIS, 1};
    m_controlData["shift"] = {ControlType::BUTTON, 2};
    m_controlData["shoot"] = {ControlType::BUTTON, 3};
    m_controlData["intake"] = {ControlType::BUTTON, 4};
    m_controlData["tiltIntake"] = {ControlType::AXIS, 5};
}

bool ControlBinding::getControlValue(std::string control) {
    auto it = m_controlData.find(control);

    // Check if control exists, then get control value
    if (it != m_controlData.end()) {
        // it->second.id;
        // it->second.type;
    } else {
        // Throw programmer-defined ControlDoesNotExistException
    }
}