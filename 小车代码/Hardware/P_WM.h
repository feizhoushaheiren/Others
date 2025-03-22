#ifndef __PWM_H
#define __PWM_H

#include "stm32f10x.h"

// 只保留TIM3的PWM初始化
void TIM3_PWM_Init(uint16_t arr, uint16_t psc);

// PWM引脚定义
#define PWM_LEFT_PIN     GPIO_Pin_6  // PA6 - TIM3_CH1，控制左侧电机
#define PWM_RIGHT_PIN    GPIO_Pin_7  // PA7 - TIM3_CH2，控制右侧电机

#endif 