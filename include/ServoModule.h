#ifndef __SERVO_MODULE_H__
#define __SERVO_MODULE_H__

#include <Arduino.h>
#include "Config.h"
#include "DirectionController.h"
#include "RadarModule.h"

class ServoModule : public DirectionController
{
public:
    /**
     * 构造函数 将自己注册为雷达模块的控制器
     */
    ServoModule(RadarModule &radar);
    void attach();
    virtual void setDirection(int angle)  override;
    virtual int getDirection() const override;
    virtual int scan() override;
    virtual bool detect() const override;
    /**
     * rotate
     * @param angleFrom  min 0
     * @param angleTo  max 180
     * @param stepSize Recommended value is 2
     * @param measure
     */
    void rotate(int angleFrom, int angleTo, int stepSize, bool measure);

    /**
     * Rotate with 2 step size
     * @param angleFrom
     * @param angleTo
     * @param measure
     */
    void rotate(int angleFrom, int angleTo, bool measure);

private:
    RadarModule &radar;
    mutable int direction;
    mutable float distance;
};

#endif