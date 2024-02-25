#include <Arduino.h>

// 右电机
#define MOTOR_R_PWM 10
#define MOTOR_R_IN1 12
#define MOTOR_R_IN2 13

// 左电机
#define MOTOR_L_PWM 9
#define MOTOR_L_IN1 7
#define MOTOR_L_IN2 8

// 电机端口初始化
void motor_init(void);
// 停止所有电机
void stop_all_motor(void);

void setup()
{
  motor_init();
  // 初始化串行接口，设置波特率为9600
  Serial.begin(9600);
}

void loop()
{
  //是电机正传 以50%占空比运行（中等速度）
  digitalWrite(MOTOR_R_IN1, HIGH);
  digitalWrite(MOTOR_R_IN2, LOW);
  analogWrite(MOTOR_R_PWM, 128); //占空比50%，占空比范围为0~255

  digitalWrite(MOTOR_L_IN1, HIGH);
  digitalWrite(MOTOR_L_IN2, LOW);
  analogWrite(MOTOR_L_PWM, 128);
  delay(5000);

  //停止左右电机
  stop_all_motor();
  delay(2000); //暂停2s


  //使左右电机反向运转
  digitalWrite(MOTOR_R_IN1, LOW);
  digitalWrite(MOTOR_R_IN2, HIGH);
  analogWrite(MOTOR_R_PWM, 128);  

  digitalWrite(MOTOR_L_IN1, LOW);
  digitalWrite(MOTOR_L_IN2, HIGH);
  analogWrite(MOTOR_L_PWM, 128);
  delay(5000);

  //停止左右电机
  stop_all_motor();
  delay(2000);

}

/**
 * 电机初始化
 */
void motor_init(void)
{
  // 设置电机方向控制引脚为输出模式
  pinMode(MOTOR_R_IN1, OUTPUT);
  pinMode(MOTOR_R_IN2, OUTPUT);
  pinMode(MOTOR_L_IN1, OUTPUT);
  pinMode(MOTOR_L_IN2, OUTPUT);
  // 设置PWM引脚为输出模式
  pinMode(MOTOR_L_PWM, OUTPUT);
  pinMode(MOTOR_R_PWM, OUTPUT);

  // 初始时关闭电机（占空比为0） 占空比的范围为0~255
  digitalWrite(MOTOR_R_IN1, LOW);
  digitalWrite(MOTOR_R_IN2, LOW);
  digitalWrite(MOTOR_R_PWM, LOW);

  digitalWrite(MOTOR_L_IN1, LOW);
  digitalWrite(MOTOR_L_IN2, LOW);
  digitalWrite(MOTOR_L_PWM, LOW);
}

/**
 * 停止所有电机
*/
void stop_all_motor(void) {
  digitalWrite(MOTOR_R_IN1, LOW);
  digitalWrite(MOTOR_R_IN2, LOW);
  digitalWrite(MOTOR_R_PWM, LOW);

  digitalWrite(MOTOR_L_IN1, LOW);
  digitalWrite(MOTOR_L_IN2, LOW);
  digitalWrite(MOTOR_L_PWM, LOW);
}