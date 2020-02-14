#include "commands/DefaultDrive.h"
#include "Cameras.h"

DefaultDrive::DefaultDrive() {
    AddRequirements({TankSubsystem::getInstance()});
}

void DefaultDrive::Initialize() {

}

void DefaultDrive::Execute() {
    double leftStick = m_driverJoystick.GetRawAxis(1);
    double rightStick = m_driverJoystick.GetRawAxis(3);

    if(m_inverted){
        //swap sides and direction
        TankSubsystem::getInstance()->setSpeed(rightStick, leftStick);
    }else{
        TankSubsystem::getInstance()->setSpeed(-leftStick, -rightStick);
    }
    

    //toggle direction using the 'B' button
    if(m_driverJoystick.GetRawButton(3)){
        if(!m_pressedBefore){
            m_inverted = !m_inverted;
            CameraHost::getInstance()->setReverse(m_inverted);
        }
        m_pressedBefore = true;
    }else{
        m_pressedBefore = false;
    }
}

void DefaultDrive::End(bool interrupted) {
    TankSubsystem::getInstance()->setSpeed(0.0, 0.0);
}

bool DefaultDrive::IsFinished() {
    return false;
}
