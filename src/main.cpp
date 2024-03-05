#include <Arduino.h>
#include "CenterControlModule.h"

CenterControlModule centerControlModule;

void setup()
{
  // 设置波特率
  Serial.begin(9600);
  // 初始化中心控制模块
  centerControlModule.setup();   
}

void loop()
{
  centerControlModule.test();
  delay(3);
}