#include "ServoModule.h"

ServoModule::ServoModule()
{
    // empty constructor
}

void ServoModule::attach(int pin)
{
    servoPin = pin;
    pinMode(pin, OUTPUT);
}

void ServoModule::setAngle(int angle)
{
    /**
     * 舵机的控制一般需要一个20ms左右的时基脉冲，高电平一般为0.5ms-2.5ms的角度控制* 脉冲部分，总间隔2ms。 以180度为例，对应关系为：
     * 0.5ms - 0度
     * 1.0ms - 45度
     * 1.5ms - 90度
     * 2.0ms - 135度
     * 2.5ms - 180度
     */
    int pulseWidth = (angle * 11) + 500;
    digitalWrite(servoPin, HIGH);
    delayMicroseconds(pulseWidth);
    digitalWrite(servoPin, LOW);
    delayMicroseconds(25000 - pulseWidth);
}

void ServoModule::rotate(int minAngle, int maxAngle, int stepSize, ServoCallback<void> callback)
{
    for (int angle = minAngle; angle <= maxAngle; angle += stepSize)
    {
        // 优化：更加稳定
        for (int i = 0; i < 2; i++)
        {
            setAngle(angle);
        }
        if (callback != NULL)
        {
            callback(angle);
        }
    }
}

void ServoModule::rotate(int minAngle, int maxAngle, ServoCallback<void> callback)
{
    rotate(minAngle, maxAngle, 2, callback);
}