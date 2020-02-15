#pragma once

#include <frc/Compressor.h>
#include <frc/Solenoid.h>
#include "Constants.h"

class PCMHandler {
    private:
        frc::Compressor compressor = frc::Compressor(1);
        frc::Solenoid highgearSol = frc::Solenoid(PCM_CAN_ID, SOLENOID_HIGH_GEAR);
        frc::Solenoid lowgearSol = frc::Solenoid(PCM_CAN_ID, SOLENOID_LOW_GEAR);
        frc::Solenoid tiltIntakeSol = frc::Solenoid(PCM_CAN_ID, SOLENOID_INTAKE_TILT);
        PCMHandler();
    public:
        static PCMHandler* getInstance() {
            static PCMHandler instance;

            return &instance;           
        }

        PCMHandler(PCMHandler const&) = delete;
        void operator = (PCMHandler const&) = delete;

        void turnOn();
        void turnOff();
        void setLowGear();
        void setHighGear();
        void activateIntakeTilt();
        void deactivateIntakeTilt();
};