#include "CenterControl.h"

CenterControl::CenterControl():servo(radar)
{
    // empty constructor
}

void CenterControl::setup()
{
    servo.attach();
    radar.attach();
    motor.attach();
    motor.setMotorGear(G3);
}

void CenterControl::test()
{
    // delay(2000); // delay 2s

    // motor.accelerateForward(G1->dutyCycle, 255, 50, 100 * 1000);

    // motor.stop();
    // delay(2000); // delay 2s

    // motor.accelerateBackward(255, 0, 50, 100 * 1000);

    // motor.stop();
    // delay(2000); // delay 2s

    // servo.swing(nullptr);
    servo.setDirection(90);
    bool r = servo.detect();
    if (r == true) {
        Serial.println("Has Obstacle, start scan...");
        servo.scan();
        Serial.println(servo.getDirection());
    } else{
        Serial.println("No Obstacle");
    }
}