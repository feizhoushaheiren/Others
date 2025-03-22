#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"



int main ()
	{
		
		OLED_Init();
		Key_Init();
		OLED_ShowChar(1,1,'A');

		while(1)
		{
			OLED_ShowNum(1,7,GetACount(),5);
		}
		
}
	
