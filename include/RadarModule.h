#ifndef __RADAR_MODULE_H__
#define __RADAR_MODULE_H__

#include <Arduino.h>

class RadarModule
{
public:
    /**
     * Constructor
     */
    RadarModule();
    /**
     * Set pin
     * @param trigPin
     * @param echoPin
     */
    void attach(int trigPin, int echoPin);

    /**
     * 测量，单位cm
     */
    float measure();

private:
    int trigPin;
    int echoPin;
};
#endif