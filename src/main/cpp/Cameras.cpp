#include "Cameras.h"

void CameraHost::init(){
    m_frontCamera = frc::CameraServer::GetInstance()->StartAutomaticCapture("Front Camera", CAMERA_FRONT);
    m_backCamera = frc::CameraServer::GetInstance()->StartAutomaticCapture("Back Camera", CAMERA_BACK);

    m_switchCam = frc::CameraServer::GetInstance()->AddSwitchedCamera("Output Stream");
    m_switchCam.SetSource(m_frontCamera);
}

void CameraHost::setReverse(bool should){
    if(should){
        m_switchCam.SetSource(m_backCamera);
    }else{
        m_switchCam.SetSource(m_frontCamera);
    }
}