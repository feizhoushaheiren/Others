#include "MotroDrive.h"
#include "P_WM.h"

void Motor_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = MOTOR_LEFT_IN1 | MOTOR_LEFT_IN2 | 
                                 MOTOR_RIGHT_IN1 | MOTOR_RIGHT_IN2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MOTOR_GPIO, &GPIO_InitStructure);
    
    Motor_Control(MOTOR_STOP);  // 初始化后停止
}

void Set_Motor_Speed(uint16_t left_speed, uint16_t right_speed)
{
    TIM_SetCompare1(TIM3, left_speed);   // 左电机速度
    TIM_SetCompare2(TIM3, right_speed);  // 右电机速度
}

void Motor_Control(uint8_t direction)
{
    switch(direction)
    {
        case MOTOR_FORWARD:  // 前进
            GPIO_SetBits(MOTOR_GPIO, MOTOR_LEFT_IN1);      // 左电机正转
            GPIO_ResetBits(MOTOR_GPIO, MOTOR_LEFT_IN2);
            GPIO_SetBits(MOTOR_GPIO, MOTOR_RIGHT_IN1);     // 右电机正转
            GPIO_ResetBits(MOTOR_GPIO, MOTOR_RIGHT_IN2);
            Set_Motor_Speed(SPEED_NORMAL, SPEED_NORMAL);   // 两轮同速
            break;
            
        case MOTOR_BACKWARD:  // 后退
            GPIO_ResetBits(MOTOR_GPIO, MOTOR_LEFT_IN1);    // 左电机反转
            GPIO_SetBits(MOTOR_GPIO, MOTOR_LEFT_IN2);
            GPIO_ResetBits(MOTOR_GPIO, MOTOR_RIGHT_IN1);   // 右电机反转
            GPIO_SetBits(MOTOR_GPIO, MOTOR_RIGHT_IN2);
            Set_Motor_Speed(SPEED_NORMAL, SPEED_NORMAL);   // 两轮同速
            break;
            
        case MOTOR_LEFT:  // 左转
            GPIO_ResetBits(MOTOR_GPIO, MOTOR_LEFT_IN1);    // 左电机反转
            GPIO_SetBits(MOTOR_GPIO, MOTOR_LEFT_IN2);
            GPIO_SetBits(MOTOR_GPIO, MOTOR_RIGHT_IN1);     // 右电机正转
            GPIO_ResetBits(MOTOR_GPIO, MOTOR_RIGHT_IN2);
            Set_Motor_Speed(SPEED_TURN, SPEED_NORMAL);     // 左轮慢，右轮快
            break;
            
        case MOTOR_RIGHT:  // 右转
            GPIO_SetBits(MOTOR_GPIO, MOTOR_LEFT_IN1);      // 左电机正转
            GPIO_ResetBits(MOTOR_GPIO, MOTOR_LEFT_IN2);
            GPIO_ResetBits(MOTOR_GPIO, MOTOR_RIGHT_IN1);   // 右电机反转
            GPIO_SetBits(MOTOR_GPIO, MOTOR_RIGHT_IN2);
            Set_Motor_Speed(SPEED_NORMAL, SPEED_TURN);     // 左轮快，右轮慢
            break;
            
        case MOTOR_STOP:  // 停止
        default:
            GPIO_ResetBits(MOTOR_GPIO, MOTOR_LEFT_IN1 | MOTOR_LEFT_IN2 | 
                                     MOTOR_RIGHT_IN1 | MOTOR_RIGHT_IN2);
            Set_Motor_Speed(0, 0);
            break;
    }
}

void Forward(void)
{
    Motor_Control(MOTOR_FORWARD);
}

void Backward(void)
{
    Motor_Control(MOTOR_BACKWARD);
}

void Leftward(void)
{
    Motor_Control(MOTOR_LEFT);
}

void Rightward(void)
{
    Motor_Control(MOTOR_RIGHT);
}

void Stop(void)
{
    Motor_Control(MOTOR_STOP);
}