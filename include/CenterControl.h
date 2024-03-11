#ifndef __CENTERCONTROL_H__
#define __CENTERCONTROL_H__

#include "ServoModule.h"
#include "RadarModule.h"
#include "MotorModule.h"



class CenterControl
{
public:
    CenterControl();
    void setup();
    void test();

private:
    RadarModule radar;
    ServoModule servo;
    MotorModule motor;
};

#endif