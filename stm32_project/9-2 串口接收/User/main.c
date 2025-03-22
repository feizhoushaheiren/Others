#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint16_t RxData;

int main ()
	{
		
		OLED_Init();
		


		while(1)
		{
			if (USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==SET)
			{
				RxData = USART_ReceiveData(USART1);
			}

		}
		
}
	
