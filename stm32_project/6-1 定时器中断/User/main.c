#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

uint16_t Num;

int main ()
	{
		
		OLED_Init();
		Timer_Init();
		OLED_ShowChar(1,1,'A');

		while(1)
		{
			OLED_ShowNum(1,5,Num,5);
		}
		
}
	
