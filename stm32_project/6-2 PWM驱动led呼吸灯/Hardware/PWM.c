#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
	{
		
		//开启时钟
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
		
		//初始化GPIO
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP ;
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 ;
		GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructure);
		//选择时钟
		TIM_InternalClockConfig(TIM2);
		//配置时基单元
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
		TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
		TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
		//有一个数的偏差
		TIM_TimeBaseInitStructure.TIM_Period=1000-1;  //ARR
		TIM_TimeBaseInitStructure.TIM_Prescaler=720-1;  //PSC
		TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
		TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
		
		TIM_OCInitTypeDef TIM_OCInitStructure;
		//给所有数据默认赋一个初始值
		TIM_OCStructInit(&TIM_OCInitStructure);
		//单独给需要设置的赋值
		TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse=0;//CCR的值
		TIM_OC1Init(TIM2,&TIM_OCInitStructure);
		
		TIM_Cmd(TIM2,ENABLE);
}
	
void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM2,Compare);
	
}

