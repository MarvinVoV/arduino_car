#ifndef __RADAR_MODULE_H__
#define __RADAR_MODULE_H__

#include <Arduino.h>
#include "Config.h"

class RadarModule
{
public:
    RadarModule();
    void attach();
    /**
     * 测量，单位cm
     */
    float measure();


private:
    int trigPin;
    int echoPin;
};
#endif