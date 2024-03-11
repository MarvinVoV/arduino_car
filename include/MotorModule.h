#ifndef __MOTOR_MODULE_H__
#define __MOTOR_MODULE_H__

#include <Arduino.h>
#include <cstdint>
#include <cmath>
// 定义轮子轴长度 mm
constexpr double WHEEL_AXLE_LEN = 150.0;
// 定义轮子直径 mm
constexpr double WHEEL_DIAMETER = 65.0;
// 轮子周长
constexpr double WHEEL_CIRCUMFERENCE = M_PI * WHEEL_DIAMETER;

struct Gear
{
    // 占空比
    int dutyCycle;
    // 车轮旋转一周所需的微秒数
    uint32_t wheelRotateMs;
    // 车轮的速度，单位毫米每微秒 mm/us
    double speed;
    /**
     * 小车旋转一周需要的时间，单位微秒
     */
    uint32_t carRotateMs;
};

// 定义五个档位
const Gear *const G1 = new Gear{80, 1253200, WHEEL_CIRCUMFERENCE / G1->wheelRotateMs, 4065000};
const Gear *const G2 = new Gear{100, 900000, WHEEL_CIRCUMFERENCE / G2->wheelRotateMs, 2740000};
const Gear *const G3 = new Gear{150, 544000, WHEEL_CIRCUMFERENCE / G3->wheelRotateMs, 2207500};
const Gear *const G4 = new Gear{200, 362500, WHEEL_CIRCUMFERENCE / G4->wheelRotateMs, 1390000};
const Gear *const G5 = new Gear{250, 266000, WHEEL_CIRCUMFERENCE / G5->wheelRotateMs, 1160000};

class MotorModule
{
public:
    /**
     *  初始化档位
     */
    MotorModule();
    ~MotorModule();
    void attach();
    /**
     * 设置电机速度
     * @param gear 电机档位
     */
    void setMotorGear(const Gear *gear);
    Gear *getMotorGear();
    /**
     * 向左旋转指定度数，即左右电机以相同速度正反转
     * @param degree 旋转度数
     */
    void rotateLeft(int degree);

    /**
     * 向右旋转指定度数，即左右电机以相同速度正反转
     * @param degree 旋转度数
     */
    void rotateRight(int degree);

    /**
     * 左右电机以相同速度正传
     */
    void forward(uint32_t delayMicrosecTime);
    /**
     * 左右电机以相同速度反转
     */
    void backward(uint32_t delayMicrosecTime);
    /**
     * 左侧电机正转
     */
    void leftForward(uint32_t delayMicrosecTime);
    
    void leftForward(int pwm, uint32_t delayMicrosecTime);

    /**
     * 右侧电机正转
     */
    void rightForward(uint32_t delayMicrosecTime);
    void rightForward(int pwd, uint32_t delayMicrosecTime);
    /**
     * 左侧电机反转
     */
    void leftBackward(uint32_t delayMicrosecTime);
    void leftBackward(int pwd, uint32_t delayMicrosecTime);
    /**
     * 右侧电机反转
     */
    void rightBackward(uint32_t delayMicrosecTime);
    void rightBackward(int pwd, uint32_t delayMicrosecTime);
    void stopLeft();
    void stopRight();
    void stop();

    /**
     * 加速前进
    */
    void accelerateForward(int initalPwd, int finalPwd, int accelerationSteps, uint32_t stepDelayMircosecTime);

    /**
     * 加速后退
    */
    void accelerateBackward(int initalPwd, int finalPwd, int accelerationSteps, uint32_t stepDelayMircosecTime);
    /**
     * 减速前进
    */
    void decelerateForward(int finalPwd, int deccelerationSteps, uint32_t stepDelayMircosecTime);

    /**
     * 减速后退
    */
    void decelerateBackward(int finalPwd, int deccelerationSteps, uint32_t stepDelayMircosecTime);

private:
    Gear gear;
};

#endif