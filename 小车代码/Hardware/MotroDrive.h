#ifndef __MOTOR_DRIVE_H
#define __MOTOR_DRIVE_H

#include "stm32f10x.h"

// 速度定义
#define SPEED_NORMAL    150      // 正常速度，从300降到50
#define SPEED_TURN      100      // 转弯时的速度，从200降到30

// 方向定义
#define MOTOR_FORWARD    0
#define MOTOR_BACKWARD   1
#define MOTOR_LEFT       2
#define MOTOR_RIGHT      3
#define MOTOR_STOP       4

// 引脚定义
#define MOTOR_LEFT_IN1    GPIO_Pin_8   // 左电机IN1
#define MOTOR_LEFT_IN2    GPIO_Pin_9   // 左电机IN2
#define MOTOR_RIGHT_IN1   GPIO_Pin_10  // 右电机IN1
#define MOTOR_RIGHT_IN2   GPIO_Pin_11  // 右电机IN2
#define MOTOR_GPIO        GPIOB

// 函数声明
void Motor_Init(void);
void Motor_Control(uint8_t direction);
void Set_Motor_Speed(uint16_t left_speed, uint16_t right_speed);

// 添加运动控制函数声明
void Forward(void);
void Backward(void);
void Leftward(void);
void Rightward(void);
void Stop(void);

#endif /* __MOTOR_DRIVE_H */