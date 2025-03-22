/*
这个文件实现了STM32F10x的串口2(USART2)通信功能,主要用于与蓝牙模块通信来控制小车。

主要功能包括:
1. 串口2初始化配置(uasrt_Init)
   - 配置PA2为发送引脚(TX),PA3为接收引脚(RX)
   - 配置串口参数:波特率可调,8位数据,1位停止位,无校验,无硬件流控
   - 使能串口接收中断

2. 串口2中断处理(USART2_IRQHandler)
   - 接收蓝牙发送的控制指令
   - 根据不同指令设置相应标志位:
     'A':前进  'B':右转  'C':左转  'D':后退  'F':停止
     'X':遥控模式  'Y/Z/R':预留功能
   - 回显接收到的指令

3. 蓝牙控制小车运动(Bluetooth_Drive)
   - 根据串口接收的标志位控制小车动作
   - 实现前进、后退、左转、右转、停止等基本运动

4. 串口发送功能(USART2_Send_Byte/String)
   - 发送单个字节
   - 发送字符串

全局变量:
- g_USART2_FLAG1: 串口控制标志位
- USART_RX_BUF[]: 接收缓冲区(200字节)
- USART_RX_STA: 接收状态标记
*/

#include "stm32f10x.h" // Device header
#include "USART.h"
#include "MotroDrive.h"
#include "Delay.h"

// 定义串口接收缓冲区大小
#define USART_REC_LEN 200

// PA2用作TX发送引脚
// PA3用作RX接收引脚

// 定义全局变量用于标志位
int g_USART2_FLAG1;
// 定义串口接收缓冲区数组
uint8_t USART_RX_BUF[USART_REC_LEN];
// 定义串口接收状态标志位
uint16_t USART_RX_STA = 0;

/**
 * @brief 串口2初始化函数
 * @param bound 波特率
 * @return void
 */
void USART2_Init(uint32_t bound)
{
    // 定义GPIO初始化结构体
    GPIO_InitTypeDef GPIO_InitStructure;
    // 定义USART初始化结构体
    USART_InitTypeDef USART_InitStructure;
    // 定义NVIC中断向量初始化结构体
    NVIC_InitTypeDef NVIC_InitStructure;

    // 使能GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    // 使能USART2时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    // 配置PA2为复用推挽输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 配置PA3为浮空输入
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 配置USART2中断
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // 配置USART2参数
    USART_InitStructure.USART_BaudRate = bound;                                  // 设置波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                 // 8位数据位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                     // 1位停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                        // 无校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无硬件流控
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;            // 收发模式
    USART_Init(USART2, &USART_InitStructure);

    // 使能USART2接收中断
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    // 使能USART2
    USART_Cmd(USART2, ENABLE);
}

/**
 * @brief USART2中断服务函数
 * @param void
 * @return void
 */
void USART2_IRQHandler(void)
{
    u8 Res;
    
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        Res = USART_ReceiveData(USART2);
        
        // 根据接收到的指令设置相应的标志位
        switch(Res)
        {
            case 'A': g_USART2_FLAG1 = 1; break;    // 前进
            case 'B': g_USART2_FLAG1 = 2; break;    // 右转
            case 'C': g_USART2_FLAG1 = 3; break;    // 左转
            case 'D': g_USART2_FLAG1 = 4; break;    // 后退
            case 'F': g_USART2_FLAG1 = 5; break;    // 停止
            case 'X': g_USART2_FLAG1 = 11; break;   // 遥控模式
            case 'Y': g_USART2_FLAG1 = 22; break;   // 预留
            case 'Z': g_USART2_FLAG1 = 33; break;   // 预留
            case 'R': g_USART2_FLAG1 = 44; break;   // 预留
            default: break;
        }
        
        // 回显收到的指令（可选）
        USART2_Send_Byte(Res);
    }
}

/**
 * @brief 蓝牙控制小车运动函数
 * @param void
 * @return void
 */
void Bluetooth_Drive(void)
{
    static uint8_t last_flag = 0;
    
    if(g_USART2_FLAG1 != last_flag)  // 只在状态改变时执行动作
    {
        last_flag = g_USART2_FLAG1;
        
        switch(g_USART2_FLAG1)
        {
            case 1:  // 前进
                Forward();
                break;
            case 2:  // 右转
                Rightward();
                Delay_ms(2000);  // 右转2秒
                Backward();
                Delay_ms(2000);  // 后退2秒
                Stop();
                break;
            case 3:  // 左转
                Leftward();
                Delay_ms(2000);  // 左转2秒
                Backward();
                Delay_ms(2000);  // 后退2秒
                Stop();
                break;
            case 4:  // 后退
                Backward();
                break;
            case 5:  // 停止
                Stop();
                break;
            default:
                break;
        }
        g_USART2_FLAG1 = 0;  // 清除标志位
    }
}

void USART2_Send_Byte(uint8_t data)
{
    while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
    USART_SendData(USART2, data);
}

void USART2_Send_String(char *str)
{
    while(*str)
    {
        USART2_Send_Byte(*str++);
    }
}