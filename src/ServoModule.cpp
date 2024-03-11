#include "ServoModule.h"

ServoModule::ServoModule(RadarModule &radar) : radar(radar),direction(0), distance(0.0)
{
}

void ServoModule::attach()
{
    pinMode(SERVO_PIN, OUTPUT);
}

void ServoModule::setDirection(int angle) 
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
    digitalWrite(SERVO_PIN, HIGH);
    delayMicroseconds(pulseWidth);
    digitalWrite(SERVO_PIN, LOW);
    delayMicroseconds(25000 - pulseWidth);
}

int ServoModule::getDirection() const
{
    return direction;
}

int ServoModule::scan() 
{
    setDirection(90);
    rotate(90, 180, true);
    setDirection(90);
    rotate(90, 0, true);
    setDirection(90);
    return getDirection();
}

bool ServoModule::detect() const
{
    float distance = radar.measure();
    if (distance > 0 && distance < 20)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ServoModule::rotate(int angleFrom, int angleTo, int stepSize, bool measure)
{
    if (angleFrom == angleTo)
    {
        setDirection(angleFrom);
        return;
    }

    if (angleFrom < angleTo)
    {
        for (int angle = angleFrom; angle <= angleTo; angle += stepSize)
        {
            // 优化：更加稳定
            for (int i = 0; i < 2; i++)
            {
                setDirection(angle);
            }
            if (measure)
            {
                float d = radar.measure();
                if (d > 0 && distance < d)
                {
                    distance = d;
                }
            }
        }
    }
    else
    {
        for (int angle = angleFrom; angle >= angleTo; angle -= stepSize)
        {
            // 优化：更加稳定
            for (int i = 0; i < 2; i++)
            {
                setDirection(angle);
            }
            if (measure)
            {
                float d = radar.measure();
                if (d > 0 && distance < d)
                {
                    distance = d;
                }
            }
        }
    }
}

void ServoModule::rotate(int angleFrom, int angleTo, bool measure)
{
    rotate(angleFrom, angleTo, 2, measure);
}
