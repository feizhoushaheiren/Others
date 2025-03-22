#include "stm32f10x.h" // Device header
#include "P_WM.h"
#include "MotroDrive.h"
#include "Delay.h"
#include "USART.h"

void System_Init(void)
{
    // 修改为20kHz PWM
    // 72MHz / (18 * 200) = 20kHz
    TIM3_PWM_Init(199, 17);  // ARR=199, PSC=17
    
    // 初始化电机
    Motor_Init();
    
    // 初始化串口2（蓝牙通信）
    USART2_Init(9600);
}

int main(void)
{
    // 系统初始化
    System_Init();
    
    // 发送启动信息
    USART2_Send_String("System Ready!\r\n");
    
    while(1)
    {
        if(g_USART2_FLAG1 == 11)  // 遥控模式
        {
            USART2_Send_String("Remote Control Mode\r\n");
            while(1)
            {
                Bluetooth_Drive();
                // 可以添加退出遥控模式的条件
            }
        }
        // 可以添加其他模式的处理
    }
}