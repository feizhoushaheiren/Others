#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "IC.h"

int main ()
	{
		
		OLED_Init();
		PWM_Init();
		IC_Init();
		PWM_SetPrescaler(720-1);
		PWM_SetCompare1(50);
		
		OLED_ShowString(1,1,"Fre:000000HZ");
		OLED_ShowString(2,1,"Duty:00%");
		while(1)
		{
			OLED_ShowNum(1,6,IC_GetFreq(),5);
			OLED_ShowNum(2,6,IC_GetDuty(),2);
		}
		
}
	
