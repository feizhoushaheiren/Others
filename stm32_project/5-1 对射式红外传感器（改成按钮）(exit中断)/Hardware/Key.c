#include "stm32f10x.h"                  // Device header
#include "Delay.h"

uint16_t count;

void Key_Init(void)
{
	//开启GPIO和AFIO的外设时钟其中EXIT,NVIC（内壳）时钟一直开启的
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	//上拉输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//配置AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource11);
	//配置EXTI
	EXTI_InitTypeDef EXIT_InitStructure;
	EXIT_InitStructure.EXTI_Line=EXTI_Line11;
	EXIT_InitStructure.EXTI_LineCmd=ENABLE;
	EXIT_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXIT_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXIT_InitStructure);
	//配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure; 
	NVIC_InitStructure.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
}

void EXTI15_10_IRQHandler(void)
	{
		if(EXTI_GetITStatus(EXTI_Line11)==SET)
			{
				count++;
				EXTI_ClearITPendingBit(EXTI_Line11);
		}

}
	
uint16_t GetACount()
{
return count;
}

uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;
	
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) ==0 )
		{
			Delay_ms(20);
			while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0);
			Delay_ms(20);
			KeyNum=1;
		
	}
	
	if( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0)
		{
			Delay_ms(20);
			while( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0);
			Delay_ms(20);
			KeyNum=2;
		
	}	
	
	return KeyNum;
}
