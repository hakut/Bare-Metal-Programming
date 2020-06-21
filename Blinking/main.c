//PA5
//AHB1
//RCC_AHB1ENR
//GPIOx_MODER 00->input (reset) 01->General purpose output mode 10->Alternate function mode 11->Analog mode
//GPIOx_ODR for port5 ODR5 would be chosen

#include "stm32f4xx.h" // Device header
void delayMs(int delay);
int main(void)
{
	RCC->AHB1ENR |= 1;		// enable GPIOA clock
	
	GPIOA->MODER |= 0x400; // 0b 0000 0000 0000 0000 0000 0100 0000 0000
													// each two bit corresponds to a port output.
	
	while(1){
		GPIOA->ODR |= 0X20;		// 0b 0010 0000 // Each bit corresponds to output
		delayMs(100);
		GPIOA->ODR &=~ 0x20; 	// Ands with inverse of 0x20 (friendly programming)
		delayMs(100);
	}
}
void delayMs(int delay)	//pseudo delay timer
{
	int i;
	for( ; delay>0; delay--){
		for(i=0; i<3195;i++);
	}
}
