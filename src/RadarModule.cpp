#include "RadarModule.h"

RadarModule::RadarModule()
{
    // empty constructor
}

void RadarModule::attach(int trigPin, int echoPin)
{
    this->trigPin = trigPin;
    this->echoPin = echoPin;

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

float RadarModule::measure()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    float distance = pulseIn(echoPin, HIGH) / 58.0;
    return distance;
}