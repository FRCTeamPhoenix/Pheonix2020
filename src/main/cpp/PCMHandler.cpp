#include "PCMHandler.h"

void PCMHandler::turnOn() { 
    compressor.SetClosedLoopControl(true);
}

void PCMHandler::turnOff() {
    compressor.SetClosedLoopControl(false);
}

void PCMHandler::setLowGear() {
    highgearSol.Set(false);
    lowgearSol.Set(true);
}

void PCMHandler::setHighGear() {
    lowgearSol.Set(false);
    highgearSol.Set(true);
}

void PCMHandler::tiltIntakeUp(bool active) {
    tiltIntakeUpSol.Set(active);
}

void PCMHandler::tiltIntakeDown(bool active) {
    tiltIntakeDownSol.Set(active);
}

PCMHandler::PCMHandler() {}