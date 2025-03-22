#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "Encoder.h"

int main ()
	{
		
		OLED_Init();
		Timer_Init();
		Encoder_Init();


		while(1)
		{
			OLED_ShowNum(1,5,Encorder_Get(),5);
		}
		
}
	
