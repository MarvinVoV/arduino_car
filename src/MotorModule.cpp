#include "MotorModule.h"
#include "Config.h"
// declare
int validDegree(int degree);

MotorModule::MotorModule()
{
}

MotorModule::~MotorModule()
{
}

void MotorModule::attach()
{
    pinMode(MOTOR_R_IN1, OUTPUT);
    pinMode(MOTOR_R_IN2, OUTPUT);
    pinMode(MOTOR_R_PWM, OUTPUT);

    pinMode(MOTOR_L_IN1, OUTPUT);
    pinMode(MOTOR_L_IN2, OUTPUT);
    pinMode(MOTOR_L_PWM, OUTPUT);

    // 初始时关闭电机（占空比为0） 占空比的范围为0~255
    stop();

    setMotorGear(G1);
}

void MotorModule::setMotorGear(const Gear *gear)
{
    if (gear != nullptr)
    {
        this->gear = *gear;
    }
    else
    {
        // default value
        this->gear = *G1;
    }
}

Gear *MotorModule::getMotorGear()
{
    return &gear;
}

void MotorModule::rotateLeft(int degree)
{
    int angle = validDegree(degree);
    double delayTime = gear.carRotateMs * (static_cast<double>(degree) / 360.0);

    rightForward(0);
    leftBackward(0);
    if (degree < 90)
    {
        delayTime += 27000.0;
    }
    delayMicroseconds(static_cast<uint32_t>(delayTime));
}
int validDegree(int degree)
{
    if (degree < 0)
    {
        return 0;
    }
    else if (degree > 360)
    {
        return degree % 360;
    }
    else
    {
        return degree;
    }
}

void MotorModule::rotateRight(int degree)
{
    int angle = validDegree(degree);
    double delayTime = gear.carRotateMs * (static_cast<double>(degree) / 360.0);

    leftForward(0);
    rightBackward(0);
    delayMicroseconds(delayTime);
}

void MotorModule::forward(uint32_t delayMicrosecTime)
{
    leftForward(0);
    rightForward(0);
    delayMicroseconds(delayMicrosecTime);
}

void MotorModule::backward(uint32_t delayMicrosecTime)
{
    leftBackward(0);
    leftBackward(0);
    delayMicroseconds(delayMicrosecTime);
}

void MotorModule::stopLeft()
{
    digitalWrite(MOTOR_L_IN1, LOW);
    digitalWrite(MOTOR_L_IN2, LOW);
    digitalWrite(MOTOR_L_PWM, LOW);
}
void MotorModule::leftForward(uint32_t delayMicrosecTime)
{
    leftForward(gear.dutyCycle, delayMicrosecTime);
}
void MotorModule::leftForward(int pwm, uint32_t delayMicrosecTime)
{
    digitalWrite(MOTOR_L_IN1, HIGH);
    digitalWrite(MOTOR_L_IN2, LOW);
    analogWrite(MOTOR_L_PWM, pwm);
    if (delayMicrosecTime > 0)
    {
        delayMicroseconds(delayMicrosecTime);
    }
}
void MotorModule::leftBackward(uint32_t delayMicrosecTime)
{
    leftBackward(gear.dutyCycle, delayMicrosecTime);
}

void MotorModule::leftBackward(int pwm, uint32_t delayMicrosecTime)
{
    digitalWrite(MOTOR_L_IN1, LOW);
    digitalWrite(MOTOR_L_IN2, HIGH);
    analogWrite(MOTOR_L_PWM, pwm);
    if (delayMicrosecTime > 0)
    {
        delayMicroseconds(delayMicrosecTime);
    }
}
void MotorModule::rightForward(int pwm, uint32_t delayMicrosecTime)
{
    digitalWrite(MOTOR_R_IN1, HIGH);
    digitalWrite(MOTOR_R_IN2, LOW);
    analogWrite(MOTOR_R_PWM, pwm);
    if (delayMicrosecTime > 0)
    {
        delayMicroseconds(delayMicrosecTime);
    }
}

void MotorModule::rightForward(uint32_t delayMicrosecTime)
{
    rightForward(gear.dutyCycle, delayMicrosecTime);
}

void MotorModule::rightBackward(uint32_t delayMicrosecTime)
{
    rightBackward(gear.dutyCycle, delayMicrosecTime);
}
void MotorModule::rightBackward(int pwm, uint32_t delayMicrosecTime)
{
    digitalWrite(MOTOR_R_IN1, LOW);
    digitalWrite(MOTOR_R_IN2, HIGH);
    analogWrite(MOTOR_R_PWM, pwm);
    if (delayMicrosecTime > 0)
    {
        delayMicroseconds(delayMicrosecTime);
    }
}
void MotorModule::stopRight()
{
    digitalWrite(MOTOR_R_IN1, LOW);
    digitalWrite(MOTOR_R_IN2, LOW);
    digitalWrite(MOTOR_R_PWM, LOW);
}
void MotorModule::stop()
{
    stopLeft();
    stopRight();
}

void MotorModule::accelerateForward(int initalPwd, int finalPwd, int accelerationSteps, uint32_t stepDelayMircosecTime)
{
    if (initalPwd < 0 || initalPwd > 255 || finalPwd < 0 || finalPwd > 255 || accelerationSteps <= 0 || stepDelayMircosecTime <= 0)
    {
        // 参数错误，不执行加速
        return;
    }
    // 计算每步增量
    double pwdIncrement = static_cast<double>(finalPwd - initalPwd) / accelerationSteps;
    // 初始化当前占空比为初始值
    int currentPwd = initalPwd;

    for (int i = 0; i < accelerationSteps; ++i)
    {
        // 更新占空比
        currentPwd += static_cast<int>(pwdIncrement);
        // 限制占空比范围
        currentPwd = constrain(currentPwd, 0, 255);
        leftForward(currentPwd, 0);
        rightForward(currentPwd, 0);
        delayMicroseconds(stepDelayMircosecTime);
    }

    // 最终设定为目标占空比
    leftForward(finalPwd, 0);
    rightForward(finalPwd, 0);
}

void MotorModule::accelerateBackward(int initalPwd, int finalPwd, int accelerationSteps, uint32_t stepDelayMircosecTime)
{
    if (initalPwd < 0 || initalPwd > 255 || finalPwd < 0 || finalPwd > 255 || accelerationSteps <= 0 || stepDelayMircosecTime <= 0)
    {
        // 参数错误，不执行加速
        return;
    }
    int currentPwd = initalPwd;
    // 计算每步增量
    double pwdIncrement = static_cast<double>(finalPwd - initalPwd) / accelerationSteps;

    for (int i = 0; i < accelerationSteps; ++i)
    {
        // 更新占空比
        currentPwd += static_cast<int>(pwdIncrement);
        // 限制占空比范围
        currentPwd = constrain(currentPwd, 0, 255);
        leftBackward(currentPwd, 0);
        rightBackward(currentPwd, 0);
        delayMicroseconds(stepDelayMircosecTime);
    }

    // 最终设定为目标占空比
    leftBackward(finalPwd, 0);
    rightBackward(finalPwd, 0);
}

void MotorModule::decelerateForward(int finalPwd, int deccelerationSteps, uint32_t stepDelayMircosecTime)
{
    if (finalPwd < 0 || finalPwd > 255 || deccelerationSteps <= 0 || deccelerationSteps <= 0)
    {
        // 参数错误，不执行减速
        return;
    }
    int currentPwd = gear.dutyCycle;
    if (currentPwd <= 0)
    {
        return;
    }
    if (currentPwd < finalPwd)
    {
        return;
    }

    double pwdIncrement = static_cast<double>(finalPwd - currentPwd) / deccelerationSteps;

    for (int i = 0; i < deccelerationSteps; ++i)
    {
        currentPwd -= static_cast<int>(pwdIncrement);
        currentPwd = constrain(currentPwd, 0, 255);
        leftForward(currentPwd, 0);
        rightForward(currentPwd, 0);
        delayMicroseconds(stepDelayMircosecTime);
    }

    // 最终设定为目标占空比
    leftForward(finalPwd, 0);
    rightForward(finalPwd, 0);
}

void MotorModule::decelerateBackward(int finalPwd, int deccelerationSteps, uint32_t stepDelayMircosecTime)
{
    if (finalPwd < 0 || finalPwd > 255 || deccelerationSteps <= 0 || deccelerationSteps <= 0)
    {
        // 参数错误，不执行减速
        return;
    }
    int currentPwd = gear.dutyCycle;
    if (currentPwd <= 0)
    {
        return;
    }
    if (currentPwd < finalPwd)
    {
        return;
    }

    double pwdIncrement = static_cast<double>(finalPwd - currentPwd) / deccelerationSteps;
    for (int i = 0; i < deccelerationSteps; ++i)
    {
        // 更新占空比
        currentPwd -= static_cast<int>(pwdIncrement);
        // 限制占空比范围
        currentPwd = constrain(currentPwd, 0, 255);
        leftBackward(currentPwd, 0);
        rightBackward(currentPwd, 0);
        delayMicroseconds(stepDelayMircosecTime);
    }

    // 最终设定为目标占空比
    leftBackward(finalPwd, 0);
    rightBackward(finalPwd, 0);
}
