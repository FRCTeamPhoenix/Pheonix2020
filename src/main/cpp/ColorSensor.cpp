#include "ColorSensor.h"
/*
ColorSensor::ColorSensor(){
    m_colorMatcher.AddColorMatch(BLUE_TARGET);
    m_colorMatcher.AddColorMatch(RED_TARGET);
    m_colorMatcher.AddColorMatch(GREEN_TARGET);
    m_colorMatcher.AddColorMatch(YELLOW_TARGET);
}

ColorSensor::~ColorSensor(){

}

frc::Color ColorSensor::getDetectedColor(){
    return m_colorSensor.GetColor();
}

std::string ColorSensor::getApproximateColor(){
    double confidence;
    frc::Color approxColor = m_colorMatcher.MatchClosestColor(m_colorSensor.GetColor(), confidence);

    if(approxColor == BLUE_TARGET){
        return "blue";
    }else if(approxColor == GREEN_TARGET){
        return "green";
    }else if(approxColor == RED_TARGET){
        return "red";
    }else if(approxColor == YELLOW_TARGET){
        return "yellow";
    }else{
        return "unknown";
    }
}
*/