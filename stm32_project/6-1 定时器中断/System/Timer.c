#include "stm32f10x.h"                  // Device header

extern uint16_t Num;

void Timer_Init(void)
	{
		//开启时钟
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
		//选择计数器
		TIM_InternalClockConfig(TIM2);
		//配置时基单元
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
		TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
		TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
		//有一个数的偏差
		TIM_TimeBaseInitStructure.TIM_Period=10000-1;
		TIM_TimeBaseInitStructure.TIM_Prescaler=7200-1;
		TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
		TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
		
		//避免一开始就进入中断
		TIM_ClearFlag(TIM2,TIM_FLAG_Update);
		TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
		
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
		NVIC_Init(&NVIC_InitStructure);
		
		TIM_Cmd(TIM2,ENABLE);
}
	

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
		{
			Num++;
			TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
			
	}

}
