#include "commands/DefaultDrive.h"
<<<<<<< HEAD
#include "ControlBinding.h"
#include "Constants.h"
=======
#include "Cameras.h"
>>>>>>> develop

DefaultDrive::DefaultDrive() {
    AddRequirements({TankSubsystem::getInstance()});
}

void DefaultDrive::Initialize() {

}

void DefaultDrive::Execute() {
    double leftStick = ControlBinding::getInstance()->getControlStatus("driveLeft", DEADZONE);
    double rightStick = ControlBinding::getInstance()->getControlStatus("driveRight", DEADZONE);

    if(m_inverted){
        //swap sides and direction
        TankSubsystem::getInstance()->setSpeed(rightStick, leftStick);
    }else{
        TankSubsystem::getInstance()->setSpeed(-leftStick, -rightStick);
    }
    

    //toggle direction using the 'B' button
    if(ControlBinding::getInstance()->getControlStatus("switchCamera") != 0) {
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
