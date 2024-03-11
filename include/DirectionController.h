#ifndef __RADAR_ROTATION_CONTROLLER_H__
#define __RADAR_ROTATION_CONTROLLER_H__
#include <Arduino.h>

class DirectionController
{
public:
    /**
     * 设置旋转的目标角度
     */
    virtual void setDirection(int angle) = 0;
    /**
     * 获取最佳无障碍物的目标角度
     * @return 最佳无障碍物角度
     */
    virtual int getDirection() const = 0;
    /**
     * 扫描可达方向 90->180->90->0
     * @return 最佳无障碍物角度
     */
    virtual int scan() = 0;

    /**
     * 前方是否有障碍物
     * @return true: 前方有障碍物
     */
    virtual bool detect() const = 0;
};

#endif