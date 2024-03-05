#include "CenterControlModule.h"

CenterControlModule::CenterControlModule()
{
    // empty constructor
}

void CenterControlModule::setup()
{
    servo.attach(static_cast<int>(Pins::SERVO_PIN));
    radar.attach(static_cast<int>(Pins::RADAR_TRIGGER_PIN), static_cast<int>(Pins::RADAR_ECHO_PIN));
}

void CenterControlModule::test()
{
    servo.rotate(0, 180, 2, NULL);
}