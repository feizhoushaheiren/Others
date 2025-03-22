#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"

/* 宏定义 */
#define USART_REC_LEN 200  // 定义最大接收字节数

/* 外部变量声明 */
extern int g_USART2_FLAG1;                    // 串口控制标志位
extern uint8_t USART_RX_BUF[USART_REC_LEN];  // 接收缓冲区
extern uint16_t USART_RX_STA;                 // 接收状态标记

/* 函数声明 */
void USART2_Init(u32 bound);     // 串口2初始化函数
void Bluetooth_Drive(void);      // 蓝牙控制小车运动函数
void USART2_Send_Byte(uint8_t data);  // 串口2发送一个字节
void USART2_Send_String(char *str);   // 串口2发送字符串

#endif