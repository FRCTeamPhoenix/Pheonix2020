#pragma once

#include <networktables/NetworkTable.h>

namespace Limelight{
    float getTx() { return nt::NetworkTable::GetTable("limelight")->GetNumber("tx", 0.0);} //-27 to 27 degrees

    float getTy() { return nt::NetworkTable::GetTable("limelight")->GetNumber("ty", 0.0);} //-20.5 to 20.5 degrees

    bool seesTarget() { return (int)nt::NetworkTable::GetTable("limelight")->GetNumber("tv", 0.0) == 0 ? false : true;}
}