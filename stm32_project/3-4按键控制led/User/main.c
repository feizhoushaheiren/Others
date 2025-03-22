#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"

uint8_t KeyNum;



int main ()
	{
		
		LED_Init();
		Key_Init();
		LED1_ON();
		while(1)
		{
			KeyNum=Key_GetNum();
			if(KeyNum==1){
				LED2_ON();				
			}
			
			if(KeyNum==2){
				LED2_OFF();
			}
			
		}
		
}
	
