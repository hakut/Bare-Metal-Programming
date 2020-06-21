#include "stm32f4xx.h"                  // Device header

int main(void)
{
	RCC->AHB1ENR |= 4; //Enables Port C
	RCC->AHB1ENR |= 1; //Enables Port A
	
	GPIOA->MODER |= 0x400;
	GPIOC->MODER |= 0;	// This is not necessary to write. Because default mode is input.
	
	while(1)
	{
		if(GPIOC->IDR & 0x2000){ // Button is at PC.13. Controlls if button pressed
			GPIOA->ODR = 0x00;	//Turn off led
		}
		else{
			GPIOA->ODR |= 0x20; //Turn on led
		}
		
	}
	
}
