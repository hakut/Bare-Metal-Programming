	/*	USART1 is usually used to download firmware to microcontroller. So, we are going to use USART 2
			APB1 bit17 = USART2
			USART2 connected to PA2
			
	
	*/
#include "stm32f4xx.h"                  // Device header
void USART2_Init(void);
void USART_write(int ch);
void delayMs(int delay);

int main(void){
		USART2_Init();
	while(1){
		USART_write('H');
		USART_write('i');
		delayMs(10);
}
}
void USART2_Init(void){
	RCC->APB1ENR |= 0x20000;  // APB1 pin 17 enable | USART2 enable
	RCC->AHB1ENR |= 1;				// AHB1 pin 0 enable  | Port A enable
	
	GPIOA->AFR[0] = 0x700;		// Setting Port A Pin 2 as AF7
	GPIOA->MODER |= 0x20;		// set PA2 to alternate function 0b 00...00 0010 0000
	
	USART2->BRR = 0x0683; //9600 @16MHz 
	USART2->CR1 = 0x0008; //Enable Tx on CR1 bit 3
	USART2->CR1 |= 0x2000; //Enable USART on CR1 bit 13
}

void USART_write(int ch){
	while(!(USART2->SR & 0x0080)){}	//Checks Tx buffer While transmission not completed do nothing
		USART2->DR = (ch & 0xFF);
}

void delayMs(int delay){
	int i;
	for(;delay>0;delay--){
		for(i=0; i<3195; i++);
	}
}
