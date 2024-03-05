#ifndef __SERVO_MODULE_H__
#define __SERVO_MODULE_H__

#include <Arduino.h>

template <typename T>
/**
 * define callback function
 * @param angle
 */
using ServoCallback = T (*)(int);

class ServoModule
{
public:
    /**
     * Constructor
     */
    ServoModule();
    /**
     * Set pin
     * @param pin
     */
    void attach(int pin);
    /**
     * Set angle
     * @param angle
     */
    void setAngle(int angle);

    /**
     * rotate
     * @param minAngle 0
     * @param maxAngle 180
     * @param stepSize Recommended value is 2
     */
    void rotate(int minAngle, int maxAngle, int stepSize, ServoCallback<void> callback);

    /**
     * Rotate with 2 step size
     * @param minAngle
     * @param maxAngle
     */
    void rotate(int minAngle, int maxAngle, ServoCallback<void> callback);
private:
    int servoPin;
};

#endif