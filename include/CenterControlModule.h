#ifndef __CENTERCONTROL_MODULE_H__
#define __CENTERCONTROL_MODULE_H__

#include "ServoModule.h"
#include "RadarModule.h"

/**
 * 引脚枚举
 */
enum class Pins : int
{
    RADAR_ECHO_PIN = 2,
    RADAR_TRIGGER_PIN = 3,
    SERVO_PIN = 4
};

class CenterControlModule
{
public:
    CenterControlModule();
    void setup();
    void test();

private:
    ServoModule servo;
    RadarModule radar;
};

#endif