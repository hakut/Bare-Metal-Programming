#include <stm32f4xx.h>

int main(){
	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= 0x400;
	
	//Configure Systick
	SysTick->LOAD = 3200000 - 1; // We use 16MHz counter and for 200 ms delay 200msX16MHz -1 because we count from 0
	SysTick->VAL = 0;
	SysTick->CTRL = 5;

	while (1)

	{
		//	Checks if count flag is set
		if (SysTick->CTRL & 0x10000)
		{
			GPIOA->ODR ^=0x20;	// Toggle LED ^= is toggle operator
		}
		
	}
	

}