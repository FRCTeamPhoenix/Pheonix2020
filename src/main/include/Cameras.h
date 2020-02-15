#pragma once

#include "cameraserver/CameraServer.h"
#include "Constants.h"

class CameraHost{
public:
    static CameraHost* getInstance(){
        static CameraHost instance;
        
        return &instance;
    }

    CameraHost(CameraHost const&) = delete;
    void operator=(CameraHost const&)  = delete;

    //start the captures
    void init();

    //switch cameras
    void setReverse(bool should = true);
private:
    CameraHost() = default;

    cs::UsbCamera m_frontCamera;
    cs::UsbCamera m_backCamera;

    cs::MjpegServer m_switchCam;
};