#include <Arduino.h>
#include "CenterControl.h"

CenterControl  centerControl;


void setup()
{
  // 设置波特率
  Serial.begin(9600);
  // 初始化中心控制模块
  centerControl.setup();
}

void loop()
{
  centerControl.test();
}